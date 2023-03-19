#include "POEX.h"
#include "Headers/Utils.h"
#include <sstream>
#include <fstream>
#include <memory>


FileCharacteristicsType operator&(const FileCharacteristicsType& first, const FileCharacteristicsType& second)
{
    return static_cast<FileCharacteristicsType>(
        static_cast<std::underlying_type_t<FileCharacteristicsType>>(first) &
        static_cast<std::underlying_type_t<FileCharacteristicsType>>(second)
        );
}

POEX::PE::PE(const std::vector<byte>& raw)
{
    this->bFile = std::make_shared<BufferFile>(raw);
    this->filepath = L"";
}

POEX::PE::PE(CString filepath)
{
    try
    {
        auto data = loadFile(filepath);
        if (data.size() <= 0)
            THROW_EXCEPTION("[ERROR] data cann't be empty.");
        this->filepath = filepath;
        this->bFile = std::make_shared<BufferFile>(data);
    }
    catch (const std::exception& ex)
    {
        THROW_EXCEPTION(ex.what());
    }
}

auto POEX::PE::GetImageDosHeader() -> ImageDosHeader
{
    return ImageDosHeader(this->bFile);
}

auto POEX::PE::GetImageNtHeader() -> ImageNtHeader
{
    return ImageNtHeader(this->bFile, GetImageDosHeader().E_lfanew());
}

auto POEX::PE::GetImageSectionHeader() -> std::vector<ImageSectionHeader>
{
    auto fHeader = GetImageNtHeader().FileHeader();
    auto oHeader = GetImageNtHeader().OptionalHeader();

    auto offset = GetImageDosHeader().E_lfanew() + ((unsigned int)fHeader.SizeOfOptionalHeader() + PE_SIGNATURE_UNTIL_MAGIC);
    auto numberOfSection = fHeader.NumberOfSection();
    auto imageBaseAddress = oHeader.ImageBase();

    std::vector<ImageSectionHeader> sectionHeaders;
    for (size_t i = 0; i < numberOfSection; i++)
        sectionHeaders.push_back(ImageSectionHeader(this->bFile, offset + static_cast<const long>(i) * SECTION_HEADER_SIZE, imageBaseAddress));

    return sectionHeaders;
}

auto POEX::PE::GetImageExportDirectory() -> std::unique_ptr<ImageExportDirectory>
{
    auto ntHeader = this->GetImageNtHeader();
    auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
    auto& exportDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Export)];
    if (exportDataDirectory->Size() == 0 || exportDataDirectory->VirtualAddress() == 0)
        return nullptr;
    auto offset = Utils::RvaToOffset(exportDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
    return std::unique_ptr<ImageExportDirectory>(
        new ImageExportDirectory(this->bFile, offset, this->GetImageSectionHeader(), std::move(exportDataDirectory)));
}

auto POEX::PE::GetImageImportDirectory() -> std::vector<std::unique_ptr<ImageImportDirectory>>
{
    std::vector<std::unique_ptr<ImageImportDirectory>> importTables;
    auto ntHeader = this->GetImageNtHeader();
    auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
    auto& importDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Import)];
    auto& iatDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::IAT)];
    if (importDataDirectory->Size() == 0 || importDataDirectory->VirtualAddress() == 0)
        return importTables;
    auto offset = Utils::RvaToOffset(importDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
    if (offset == 0)
        return importTables;

    unsigned int iterator = 0;

    while (true)
    {
        auto imageImportDirectory = std::unique_ptr<ImageImportDirectory>(new ImageImportDirectory(this->bFile, 
            offset + IMPORT_TABLE_SIZE * iterator, this->GetImageSectionHeader(), iatDataDirectory->VirtualAddress(), this->Is64Bit()));

        // Found the last ImageImportDescriptor which is completely null (except TimeDateStamp).
        if (imageImportDirectory->ImportLookupTable() == 0 &&
                imageImportDirectory->ForwarderChain() == 0 &&
                imageImportDirectory->Name() == 0 &&
                imageImportDirectory->ImportAddressTable() == 0)
            break;

        importTables.push_back(std::move(imageImportDirectory));
        iterator++;
    }

    return importTables;
}

auto POEX::PE::GetImageResourceDirectory() -> std::unique_ptr<ImageResourceDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& resourceDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Resource)];
        auto offset = Utils::RvaToOffset(resourceDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        
        return std::make_unique<ImageResourceDirectory>(this->bFile, offset, offset, resourceDataDirectory->Size());
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageExceptionDirectory() -> std::unique_ptr<ImageExceptionDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& exceptionDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Exception)];
        auto offset = Utils::RvaToOffset(exceptionDataDirectory->VirtualAddress(), this->GetImageSectionHeader());

        return std::unique_ptr<ImageExceptionDirectory>(
            new ImageExceptionDirectory(this->bFile, offset, this->GetImageSectionHeader(), this->Is32Bit(), 
                exceptionDataDirectory->Size()));
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageTlsDirectory() -> std::unique_ptr<ImageTlsDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& tlsDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::TLS)];
        auto offset = Utils::RvaToOffset(tlsDataDirectory->VirtualAddress(), this->GetImageSectionHeader());

        return std::unique_ptr<ImageTlsDirectory>(new ImageTlsDirectory(this->bFile, offset, 
            this->GetImageSectionHeader(), this->Is64Bit()));
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageLoadConfigDirectory() -> std::unique_ptr<ImageLoadConfigDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& configDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::LoadConfig)];
        auto offset = Utils::RvaToOffset(configDataDirectory->VirtualAddress(), this->GetImageSectionHeader());

        return std::unique_ptr<ImageLoadConfigDirectory>(new ImageLoadConfigDirectory(this->bFile, 
            offset,
            this->Is64Bit()));
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageBaseRelocation() -> std::vector<std::unique_ptr<ImageBaseRelocation>>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& relocationDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::BaseReloc)];
        auto offset = Utils::RvaToOffset(relocationDataDirectory->VirtualAddress(), 
            this->GetImageSectionHeader());
        std::vector<std::unique_ptr<ImageBaseRelocation>> imageBaseRelocations;
        auto currentBlock = offset;

        while (true)
        {
            if (currentBlock >= offset + relocationDataDirectory->Size() - 8)
                break;
            imageBaseRelocations.push_back(std::make_unique<ImageBaseRelocation>(this->bFile, 
                currentBlock, relocationDataDirectory->Size()));
            currentBlock += imageBaseRelocations.back()->SizeOfBlock();
        }

        return imageBaseRelocations;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageDelayImportDescriptor() -> std::unique_ptr<ImageDelayImportDescriptor>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& delayImportDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::DelayImport)];
        auto offset = Utils::RvaToOffset(delayImportDataDirectory->VirtualAddress(),
            this->GetImageSectionHeader());

        return std::make_unique<ImageDelayImportDescriptor>(this->bFile, offset);
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageDebugDirectory() -> std::vector<std::unique_ptr<ImageDebugDirectory>>
{
    try
    {
        auto debugEntrySize = 28;
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& debugDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::Debug)];
        auto offset = Utils::RvaToOffset(debugDataDirectory->VirtualAddress(),
            this->GetImageSectionHeader());

        auto numEntries = debugDataDirectory->Size() / debugEntrySize;
        std::vector<std::unique_ptr<ImageDebugDirectory>> debugDirectories;
        for (size_t i = 0; i < numEntries; i++)
            debugDirectories.push_back(std::make_unique<ImageDebugDirectory>(this->bFile, offset));
        return debugDirectories;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::Is64Bit() const -> bool
{
    return this->bFile->ReadUnsignedShort(this->bFile->ReadUnsignedInt(ELFANEW) + PE_SIGNATURE_UNTIL_MAGIC) == (unsigned short)FileType::BIT64;
}

auto POEX::PE::Is32Bit() const -> bool
{
    return this->bFile->ReadUnsignedShort(this->bFile->ReadUnsignedInt(ELFANEW) + PE_SIGNATURE_UNTIL_MAGIC) == (unsigned short)FileType::BIT32;
}

auto POEX::PE::IsExe() -> bool
{
    return (unsigned short)FileCharacteristicsType::ExecutableImage & (unsigned short)(FileCharacteristicsType)GetImageNtHeader().FileHeader().Characteristics();
}

auto POEX::PE::IsDll() -> bool
{
    return (unsigned short)FileCharacteristicsType::Dll & (unsigned short)(FileCharacteristicsType)GetImageNtHeader().FileHeader().Characteristics();
}

auto POEX::PE::SaveFile() -> void
{
    if (this->filepath.IsEmpty())
        THROW_EXCEPTION("[ERROR] File path is empty.");
    SaveFile(this->filepath);
}

auto POEX::PE::SaveFile(const CString& filepath) -> void
{
    try
    {
        std::ofstream ofs(filepath, std::ios::binary | std::ios::out);
        auto data = this->bFile->Data();
        ofs.write((const char*)&data[0], data.size());
    }
    catch (const std::exception& ex)
    {
        THROW_EXCEPTION((std::string("[Error]") + ex.what()).c_str());
    }
}

auto POEX::PE::loadFile(const CString& filePath) -> std::vector<byte>
{
    if (filePath.IsEmpty())
        THROW_OUT_OF_RANGE("[ERROR] filepath cann't be empty.");
    std::ifstream ifs(filePath, std::ios::binary | std::ios::ate);
    if (!ifs)
        THROW_RUNTIME("[ERROR] Reading file fail.");


    auto end = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    auto size = std::size_t(end - ifs.tellg());

    if (size == 0) // avoid undefined behavior 
        THROW_RUNTIME("[ERROR] Somethings wrong in loading file.");

    std::vector<byte> buffer(size);
    if (!ifs.read((char*)buffer.data(), buffer.size()))
        throw std::runtime_error("[ERROR] Reading file fail.");

    return buffer;
}
