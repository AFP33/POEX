#include "POEX.h"
#include "Headers/Utils.h"
#include <sstream>
#include <fstream>
#include <memory>

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

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
        throw ex;
    }
}

auto POEX::PE::GetImageDosHeader() -> ImageDosHeader
{
    try
    {
        return ImageDosHeader(this->bFile);
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageNtHeader() -> ImageNtHeader
{
    try
    {
        return ImageNtHeader(this->bFile, GetImageDosHeader().E_lfanew());
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageSectionHeader() -> std::vector<std::shared_ptr<ImageSectionHeader>>
{
    try
    {
        auto fHeader = GetImageNtHeader().FileHeader();
        auto oHeader = GetImageNtHeader().OptionalHeader();

        auto offset = GetImageDosHeader().E_lfanew() + ((unsigned int)fHeader.SizeOfOptionalHeader() + PE_SIGNATURE_UNTIL_MAGIC);
        auto numberOfSection = fHeader.NumberOfSection();
        auto imageBaseAddress = oHeader.ImageBase();

        std::vector<std::shared_ptr<ImageSectionHeader>> sectionHeaders;
        for (size_t i = 0; i < numberOfSection; i++)
            sectionHeaders.push_back(std::make_shared<ImageSectionHeader>(this->bFile, offset + static_cast<const long>(i) * SECTION_HEADER_SIZE, imageBaseAddress));

        return sectionHeaders;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageExportDirectory() -> std::unique_ptr<ImageExportDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& exportDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Export)];
        if (!IsValidDataDirectory(exportDataDirectory))
            return NULL;
        auto offset = Utils::RvaToOffset(exportDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;
        return std::unique_ptr<ImageExportDirectory>(
            new ImageExportDirectory(this->bFile, offset, this->GetImageSectionHeader(), std::move(exportDataDirectory)));
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageImportDirectory() -> std::vector<std::unique_ptr<ImageImportDirectory>>
{
    try
    {
        std::vector<std::unique_ptr<ImageImportDirectory>> importTables;
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& importDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Import)];
        auto& iatDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::IAT)];
        if (!IsValidDataDirectory(importDataDirectory) || !IsValidDataDirectory(iatDataDirectory))
            return importTables;

        auto offset = Utils::RvaToOffset(importDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
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
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageResourceDirectory() -> std::unique_ptr<ImageResourceDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& resourceDataDirectory = dataDirectories[static_cast<int>(DataDirectoryType::Resource)];
        if (!IsValidDataDirectory(resourceDataDirectory))
            return NULL;
        auto offset = Utils::RvaToOffset(resourceDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;
        
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
        if (!IsValidDataDirectory(exceptionDataDirectory))
            return NULL;
        auto offset = Utils::RvaToOffset(exceptionDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;

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
        if (!IsValidDataDirectory(tlsDataDirectory))
            return NULL;

        auto offset = Utils::RvaToOffset(tlsDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;

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
        if (!IsValidDataDirectory(configDataDirectory))
            return NULL;

        auto offset = Utils::RvaToOffset(configDataDirectory->VirtualAddress(), this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;

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
        std::vector<std::unique_ptr<ImageBaseRelocation>> imageBaseRelocations;
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& relocationDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::BaseReloc)];
        if (!IsValidDataDirectory(relocationDataDirectory))
            return imageBaseRelocations;
            
        auto offset = Utils::RvaToOffset(relocationDataDirectory->VirtualAddress(), 
            this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return imageBaseRelocations;

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
        if (!IsValidDataDirectory(delayImportDataDirectory))
            return NULL;

        auto offset = Utils::RvaToOffset(delayImportDataDirectory->VirtualAddress(),
            this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;

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
        std::vector<std::unique_ptr<ImageDebugDirectory>> debugDirectories;
        auto debugEntrySize = 28;
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& debugDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::Debug)];
        if (!IsValidDataDirectory(debugDataDirectory))
            return debugDirectories;

        auto offset = Utils::RvaToOffset(debugDataDirectory->VirtualAddress(),
            this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return debugDirectories;

        auto numEntries = debugDataDirectory->Size() / debugEntrySize;
        for (size_t i = 0; i < numEntries; i++)
            debugDirectories.push_back(std::make_unique<ImageDebugDirectory>(this->bFile, offset));
        return debugDirectories;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageBoundImportDirectory() -> std::unique_ptr<ImageBoundImport>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& boundImportDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::BoundImport)];
        if (!IsValidDataDirectory(boundImportDataDirectory))
            return NULL;

        auto offset = Utils::RvaToOffset(boundImportDataDirectory->VirtualAddress(),
            this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;

        return std::make_unique<ImageBoundImport>(this->bFile, offset);
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageCertificateDirectory() -> std::unique_ptr<ImageCertificateDirectory>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& securityDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::Security)];
        if (!IsValidDataDirectory(securityDataDirectory))
            return NULL;

        // The security directory is the only one where the DATA_DIRECTORY VirtualAddress 
        // is not an RVA but an raw offset.
        return std::make_unique<ImageCertificateDirectory>(this->bFile, securityDataDirectory->VirtualAddress());
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::GetImageComDescriptor() -> std::unique_ptr<ImageComDescriptor>
{
    try
    {
        auto ntHeader = this->GetImageNtHeader();
        auto dataDirectories = ntHeader.OptionalHeader().DataDirectory();
        auto& comDescriptorDataDirectory = dataDirectories[static_cast<int>(
            DataDirectoryType::ComDescriptor)];
        if (!IsValidDataDirectory(comDescriptorDataDirectory))
            return NULL;

        auto offset = Utils::RvaToOffset(comDescriptorDataDirectory->VirtualAddress(),
            this->GetImageSectionHeader());
        if (WRONG_LONG(offset))
            return NULL;

        return std::make_unique<ImageComDescriptor>(this->bFile, offset);
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::Is64Bit() const -> bool
{
    try
    {
        return this->bFile->ReadUnsignedShort(this->bFile->ReadUnsignedInt(ELFANEW) + PE_SIGNATURE_UNTIL_MAGIC) 
            == (unsigned short)FileType::BIT64;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::Is32Bit() const -> bool
{
    try
    {
        return this->bFile->ReadUnsignedShort(this->bFile->ReadUnsignedInt(ELFANEW) + PE_SIGNATURE_UNTIL_MAGIC)
            == (unsigned short)FileType::BIT32;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::IsExe() -> bool
{
    try
    {
        return (unsigned short)FileCharacteristicsType::ExecutableImage &
            (unsigned short)(FileCharacteristicsType)GetImageNtHeader().FileHeader().Characteristics();
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::IsDll() -> bool
{
    try
    {
        return (unsigned short)FileCharacteristicsType::Dll &
            (unsigned short)(FileCharacteristicsType)GetImageNtHeader().FileHeader().Characteristics();
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::SaveFile() -> void
{
    try
    {
        if (this->filepath.IsEmpty())
            THROW_EXCEPTION("[ERROR] File path is empty.");
        SaveFile(this->filepath);
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
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

auto POEX::PE::IsValidDataDirectory(const std::unique_ptr<ImageDataDirectory>& dataDirectory) -> bool
{
    try
    {
        if (dataDirectory->Size() == 0 || dataDirectory->VirtualAddress() == 0)
            return false;
        return true;
    }
    catch (const std::exception& ex)
    {
        throw ex;
    }
}

auto POEX::PE::loadFile(const CString& filePath) -> std::vector<byte>
{
    try
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
    catch (const std::exception& ex)
    {
        throw ex;
    }
}
