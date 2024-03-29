#include "../Headers/ImageImportDirectory.h"
#include "../Headers/Utils.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageImportDirectory::ImageImportDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders, const unsigned int& iatVirtualSize,
	bool is64Bit) : bFile(bFile), offset(offset), imageSectionHeaders(imageSectionHeaders), 
	iatVirtualSize(iatVirtualSize), is64Bit(is64Bit)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageImportDirectory::ImportLookupTable() const -> unsigned int
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

auto ImageImportDirectory::ImportLookupTable(const unsigned int& importLookupTable) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, importLookupTable);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageImportDirectory::TimeDateStamp() const -> unsigned int
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

auto ImageImportDirectory::TimeDateStamp(const unsigned int& timeDateStamp) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, timeDateStamp);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageImportDirectory::ForwarderChain() const -> unsigned int
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

auto ImageImportDirectory::ForwarderChain(const unsigned int& forwarderChain) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0008, forwarderChain);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageImportDirectory::Name() const -> unsigned int
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

auto ImageImportDirectory::Name(const unsigned int& name) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000C, name);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageImportDirectory::ImportAddressTable() const -> unsigned int
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

auto ImageImportDirectory::ImportAddressTable(const unsigned int& importAddressTable) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000C, importAddressTable);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageImportDirectory::GetImportedFunctions() -> std::vector<ImportFunction>
{
	try
	{
		if (this->ImportLookupTable() == 0 &&
			this->ForwarderChain() == 0 &&
			this->Name() == 0 &&
			this->ImportAddressTable() == 0)
			return std::vector<ImportFunction>();

		auto sizeOfThunk = (unsigned int)(is64Bit ? IMAGE_THUNK_DATA_64 : IMAGE_THUNK_DATA_86); // Size of ImageThunkData
		auto ordinalBit = is64Bit ? ORDINAL_BIT_64 : ORDINAL_BIT_86;
		auto ordinalMask = (unsigned long)(is64Bit ? ORDINAL_MASK_64 : ORDINAL_MASK_86);

		auto dllAddress = Utils::RvaToOffset(this->Name(), imageSectionHeaders);
		auto dll = this->bFile->ReadAsciiString(dllAddress);
		auto tempAddress = this->ImportLookupTable() != 0 ? this->ImportLookupTable() : this->ImportAddressTable();
		if (tempAddress == 0)
			return std::vector<ImportFunction>();

		auto thunkAddress = Utils::RvaToOffset(tempAddress, imageSectionHeaders);
		unsigned int iterator = 0;
		std::vector<ImportFunction> importFunctions;

		while (true)
		{
			auto offset = thunkAddress + iterator * sizeOfThunk;
			auto addressOfData = this->is64Bit ? this->bFile->ReadUnsignedLong(offset) : this->bFile->ReadUnsignedInt(offset);
			if (addressOfData == 0)
				break;
			auto iatOffset = this->ImportAddressTable() + iterator * sizeOfThunk - iatVirtualSize;

			// import by ordinal
			if ((addressOfData & ordinalBit) == ordinalBit)
				importFunctions.push_back(ImportFunction(std::string(), dll, (unsigned short)(addressOfData & ordinalMask), iatOffset));
			else // import by name
			{
				auto baseOffset = Utils::RvaToOffset(addressOfData, imageSectionHeaders);
				auto hint = this->bFile->ReadUnsignedShort(baseOffset);
				auto name = this->bFile->ReadAsciiString(baseOffset + 0x0002);
				importFunctions.push_back(ImportFunction(name, dll, hint, iatOffset));
			}
			iterator++;
		}

		return importFunctions;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
