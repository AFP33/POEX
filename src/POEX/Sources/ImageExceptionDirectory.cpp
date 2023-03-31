#include "../Headers/ImageExceptionDirectory.h"
#include "../Headers/Utils.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageExceptionDirectory::ImageExceptionDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders, const bool& is32Bit,
	const unsigned int& directorySize) :
	bFile(bFile), offset(offset), imageSectionHeaders(imageSectionHeaders), 
	is32Bit(is32Bit), directorySize(directorySize)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageExceptionDirectory::GetExceptionDirectories() -> std::vector<std::unique_ptr<ExceptionTable>>
{
	try
	{
		if (is32Bit || offset == 0)
			return std::vector<std::unique_ptr<ExceptionTable>>();

		const int sizeOfRuntimeFunction = 0xC;
		auto numberOfFunction = directorySize / sizeOfRuntimeFunction;
		std::vector<std::unique_ptr<ExceptionTable>> exceptionTables;
		for (size_t i = 0; i < numberOfFunction; i++)
		{
			exceptionTables.push_back(std::make_unique<ExceptionTable>(this->bFile, 
				(long)(this->offset + i * sizeOfRuntimeFunction), this->imageSectionHeaders));
		}

		return exceptionTables;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

ExceptionTable::ExceptionTable(const std::shared_ptr<BufferFile>& bFile, const long& offset,
	const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders) :
	bFile(bFile), offset(offset), imageSectionHeaders(imageSectionHeaders)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ExceptionTable::BeginAddress() const -> unsigned long
{
	try
	{
		return this->bFile->ReadUnsignedLong(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ExceptionTable::BeginAddress(const unsigned long& offset) -> void
{
	try
	{
		this->bFile->WriteUnsignedLong(this->offset + 0x0000, offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ExceptionTable::EndAddress() const -> unsigned long
{
	try
	{
		return this->bFile->ReadUnsignedLong(this->offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ExceptionTable::EndAddress(const unsigned long& offset) -> void
{
	try
	{
		this->bFile->WriteUnsignedLong(this->offset + 0x0004, offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ExceptionTable::UnwInfo() const -> unsigned long
{
	try
	{
		return this->bFile->ReadUnsignedLong(this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ExceptionTable::UnwInfo(const unsigned long& pointer) -> void
{
	try
	{
		this->bFile->WriteUnsignedLong(this->offset + 0x0008, pointer);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}