#include "../Headers/ImageExportDirectory.h"
#include "../Headers/Utils.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageExportDirectory::ImageExportDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders, std::unique_ptr<ImageDataDirectory> imageDataDirectory) :
	bFile(bFile), offset(offset), imageSectionHeaders(imageSectionHeaders), imageDataDirectory(std::move(imageDataDirectory))
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageExportDirectory::Characteristics() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::Characteristics(const unsigned int& characteristics) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0000, characteristics);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::TimeDateStamp() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::TimeDateStamp(const unsigned int& timeDateStamp) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0004, timeDateStamp);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::MajorVersion() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::MajorVersion(const unsigned short& majorVersion) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0008, majorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::MinorVersion() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x000A);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::MinorVersion(const unsigned short& minorVersion) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x000A, minorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::Name() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x000C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::Name(const unsigned int& name) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x000C, name);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::Base() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0010);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::Base(const unsigned int& base) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0010, base);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::NumberOfFunctions() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0014);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::NumberOfFunctions(const unsigned int& numberOfFunctions) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0014, numberOfFunctions);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::NumberOfNames() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0018);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::NumberOfNames(const unsigned int& numberOfNames) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0018, numberOfNames);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::AddressOfFunctions() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x001C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::AddressOfFunctions(const unsigned int& addressOfFunctions) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x001C, addressOfFunctions);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::AddressOfNames() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0020);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::AddressOfNames(const unsigned int& addressOfNames) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0020, addressOfNames);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::AddressOfNameOrdinals() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x0024);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::AddressOfNameOrdinals(const unsigned int& addressOfNameOrdinals) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x0024, addressOfNameOrdinals);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::GetExportFunctions() -> std::vector<ExportFunction>
{
	try
	{
		if (imageDataDirectory == nullptr || this->AddressOfFunctions() == 0)
			return std::vector<ExportFunction>();

		auto expFuncs = std::vector<ExportFunction>();
		auto funcOffsetPointer = Utils::RvaToOffset(this->AddressOfFunctions(), imageSectionHeaders);
		auto ordOffset = this->NumberOfNames() == 0 ? 0 : Utils::RvaToOffset(this->AddressOfNameOrdinals(), imageSectionHeaders);
		auto nameOffsetPointer = this->NumberOfNames() == 0 ? 0 : Utils::RvaToOffset(this->AddressOfNames(), imageSectionHeaders);

		for (unsigned int i = 0; i < this->NumberOfFunctions(); i++)
		{
			auto ordinal = this->Base() + i;
			auto address = this->bFile->ReadUnsignedInt(funcOffsetPointer + sizeof(unsigned int) * i);

			auto ef = ExportFunction(std::string(), address, static_cast<unsigned short>(ordinal));
			expFuncs.push_back(ef);
		}

		for (unsigned int i = 0; i < this->NumberOfNames(); i++)
		{
			auto namePtr = this->bFile->ReadUnsignedInt(nameOffsetPointer + sizeof(unsigned int) * i);
			auto nameAdr = Utils::RvaToOffset(namePtr, imageSectionHeaders);
			auto name = this->bFile->ReadAsciiString(nameAdr);
			auto ordinalIndex = (unsigned int)this->bFile->ReadUnsignedShort(ordOffset + sizeof(unsigned short) * i);

			auto expFunc = expFuncs.at(ordinalIndex);
			if (IsForwardedExport(expFunc.Address))
			{
				auto forwardNameAdr = Utils::RvaToOffset(expFunc.Address, imageSectionHeaders);
				auto forwardName = this->bFile->ReadAsciiString(forwardNameAdr);


				auto ef = ExportFunction(name, expFunc.Address, expFunc.Ordinal, forwardName);
				expFuncs.at(ordinalIndex) = ef;
			}
			else
			{
				auto ef = ExportFunction(name, expFunc.Address, expFunc.Ordinal);
				expFuncs.at(ordinalIndex) = ef;
			}
		}
		return expFuncs;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageExportDirectory::IsForwardedExport(const unsigned int& address) -> bool
{
	try
	{
		return imageDataDirectory->VirtualAddress() <= address &&
			address < imageDataDirectory->VirtualAddress() + imageDataDirectory->Size();
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}