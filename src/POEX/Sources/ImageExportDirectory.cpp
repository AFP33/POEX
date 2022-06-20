#include "../Headers/ImageExportDirectory.h"
#include "../Headers/Utils.h"

ImageExportDirectory::ImageExportDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const std::vector<ImageSectionHeader>& imageSectionHeaders, std::unique_ptr<ImageDataDirectory> imageDataDirectory) :
	bFile(bFile), offset(offset), imageSectionHeaders(imageSectionHeaders), imageDataDirectory(std::move(imageDataDirectory))
{
}

auto ImageExportDirectory::Characteristics() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0000);
}

auto ImageExportDirectory::Characteristics(const unsigned int& characteristics) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0000, characteristics);
}

auto ImageExportDirectory::TimeDateStamp() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0004);
}

auto ImageExportDirectory::TimeDateStamp(const unsigned int& timeDateStamp) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0004, timeDateStamp);
}

auto ImageExportDirectory::MajorVersion() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0008);
}

auto ImageExportDirectory::MajorVersion(const unsigned short& majorVersion) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0008, majorVersion);
}

auto ImageExportDirectory::MinorVersion() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x000A);
}

auto ImageExportDirectory::MinorVersion(const unsigned short& minorVersion) -> void
{
	bFile->WriteUnsignedShort(offset + 0x000A, minorVersion);
}

auto ImageExportDirectory::Name() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x000C);
}

auto ImageExportDirectory::Name(const unsigned int& name) -> void
{
	bFile->WriteUnsignedInt(offset + 0x000C, name);
}

auto ImageExportDirectory::Base() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0010);
}

auto ImageExportDirectory::Base(const unsigned int& base) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0010, base);
}

auto ImageExportDirectory::NumberOfFunctions() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0014);
}

auto ImageExportDirectory::NumberOfFunctions(const unsigned int& numberOfFunctions) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0014, numberOfFunctions);
}

auto ImageExportDirectory::NumberOfNames() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0018);
}

auto ImageExportDirectory::NumberOfNames(const unsigned int& numberOfNames) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0018, numberOfNames);
}

auto ImageExportDirectory::AddressOfFunctions() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x001C);
}

auto ImageExportDirectory::AddressOfFunctions(const unsigned int& addressOfFunctions) -> void
{
	bFile->WriteUnsignedInt(offset + 0x001C, addressOfFunctions);
}

auto ImageExportDirectory::AddressOfNames() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0020);
}

auto ImageExportDirectory::AddressOfNames(const unsigned int& addressOfNames) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0020, addressOfNames);
}

auto ImageExportDirectory::AddressOfNameOrdinals() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x0024);
}

auto ImageExportDirectory::AddressOfNameOrdinals(const unsigned int& addressOfNameOrdinals) -> void
{
	bFile->WriteUnsignedInt(offset + 0x0024, addressOfNameOrdinals);
}

auto ImageExportDirectory::GetExportFunctions() -> std::vector<ExportFunction>
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

auto ImageExportDirectory::IsForwardedExport(const unsigned int& address) -> bool
{
	return imageDataDirectory->VirtualAddress() <= address && 
		address < imageDataDirectory->VirtualAddress() + imageDataDirectory->Size();
}