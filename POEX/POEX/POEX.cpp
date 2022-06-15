#include "POEX.h"
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
    return POEX::ImageNtHeader(this->bFile, GetImageDosHeader().E_lfanew());
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
        sectionHeaders.push_back(POEX::ImageSectionHeader(this->bFile, offset + static_cast<const long>(i) * SECTION_HEADER_SIZE, imageBaseAddress));

    return sectionHeaders;
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
