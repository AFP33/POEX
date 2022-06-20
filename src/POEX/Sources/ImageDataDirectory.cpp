#include "../Headers/ImageDataDirectory.h"

ImageDataDirectory::ImageDataDirectory(const std::shared_ptr<BufferFile>& bFile,
	const long& offset,
	const DataDirectoryType& dataDirectoryType) : bFile(bFile), offset(offset), dataDirectoryType(dataDirectoryType)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageDataDirectory::VirtualAddress() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0000);
}

auto ImageDataDirectory::VirtualAddress(const unsigned int& virtualAddress) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0000, virtualAddress);
}

auto ImageDataDirectory::Size() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0004);
}

auto ImageDataDirectory::Size(const unsigned int& size) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0004, size);
}
