#include "../Headers/ImageNtHeader.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageNtHeader::ImageNtHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageNtHeader::Signature() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x000000);
	}
	catch (const std::exception& ex) 
	{
		throw ex;
	}
}

auto ImageNtHeader::Signature(const unsigned int& sig) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000000, sig);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageNtHeader::FileHeader() const -> ImageFileHeader
{
	try
	{
		return ImageFileHeader(this->bFile, this->offset + 0x000004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageNtHeader::OptionalHeader() const -> ImageOptionalHeader
{
	try
	{
		auto is64Bit =
			this->bFile->ReadUnsignedShort(this->bFile->ReadUnsignedInt(0x003C) + 0x0018)
			== unsigned short(FileType::BIT64);
		return ImageOptionalHeader(this->bFile, this->offset + 0x000018, is64Bit);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}