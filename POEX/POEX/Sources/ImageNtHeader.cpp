#include "../Headers/ImageNtHeader.h"

POEX::ImageNtHeader::ImageNtHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto POEX::ImageNtHeader::Signature() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x000000);
}

auto POEX::ImageNtHeader::Signature(const unsigned int& sig) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x000000, sig);
}

auto POEX::ImageNtHeader::FileHeader() const -> ImageFileHeader
{
	return ImageFileHeader(this->bFile, this->offset + 0x000004);
}

auto POEX::ImageNtHeader::OptionalHeader() const -> ImageOptionalHeader
{
	auto is64Bit = 
		this->bFile->ReadUnsignedShort(this->bFile->ReadUnsignedInt(0x003C) + 0x0018) 
		== unsigned short(FileType::BIT64);
	return ImageOptionalHeader(this->bFile, this->offset + 0x000018, is64Bit);
}