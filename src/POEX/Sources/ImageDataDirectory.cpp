#include "../Headers/ImageDataDirectory.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageDataDirectory::ImageDataDirectory(const std::shared_ptr<BufferFile>& bFile,
	const long& offset,
	const DataDirectoryType& dataDirectoryType) : bFile(bFile), offset(offset), dataDirectoryType(dataDirectoryType)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

ImageDataDirectory::ImageDataDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset) :
	bFile(bFile), offset(offset)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageDataDirectory::VirtualAddress() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDataDirectory::VirtualAddress(const unsigned int& virtualAddress) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, virtualAddress);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDataDirectory::Size() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDataDirectory::Size(const unsigned int& size) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, size);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
