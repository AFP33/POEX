#include "../Headers/ImageDelayImportDescriptor.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageDelayImportDescriptor::ImageDelayImportDescriptor(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageDelayImportDescriptor::Attributes() const -> unsigned int
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

auto ImageDelayImportDescriptor::Attributes(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::DllNameRVA() const -> unsigned int
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

auto ImageDelayImportDescriptor::DllNameRVA(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::ModuleHandleRVA() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::ModuleHandleRVA(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0008, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::ImportAddressTableRVA() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x000C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::ImportAddressTableRVA(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000C, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::ImportNameTableRVA() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0010);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::ImportNameTableRVA(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0010, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::BoundImportAddressTableRVA() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0014);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::BoundImportAddressTableRVA(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0014, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::UnloadInformationTableRVA() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0018);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::UnloadInformationTableRVA(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0018, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::TimeDateStamp() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x001C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDelayImportDescriptor::TimeDateStamp(const unsigned int& off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x001C, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
