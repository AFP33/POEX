#include "../Headers/ImageBoundImport.h"

ImageBoundImport::ImageBoundImport(const std::shared_ptr<BufferFile>& bFile, const long& offset) 
	: bFile(bFile), offset(offset)
{
}

auto ImageBoundImport::TimeDateStamp() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBoundImport::TimeDateStamp(const unsigned int& time) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, time);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBoundImport::OffsetModuleName() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBoundImport::OffsetModuleName(const unsigned short& offs) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, offs);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBoundImport::NumberOfModuleForwarderRefs() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x0006);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBoundImport::NumberOfModuleForwarderRefs(const unsigned short& refs) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0006, refs);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
