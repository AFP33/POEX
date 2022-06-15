#include "../Headers/ImageOptionalHeader.h"

POEX::ImageOptionalHeader::ImageOptionalHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, 
	const bool& is64Bit) : bFile(bFile), offset(offset), is64Bit(is64Bit)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto POEX::ImageOptionalHeader::ToString(SubsystemType subsystem) -> std::string
{
	switch (subsystem)
	{
		case SubsystemType::Unknown: return "Unknown Subsystem";
		case SubsystemType::Native:return "Native";
		case SubsystemType::WindowsGui:return "Windows Gui";
		case SubsystemType::WindowsCui:return "Windows Cui";
		case SubsystemType::Os2Cui:return "OS/2 CUI";
		case SubsystemType::PosixCui:return "POSIX CUI";
		case SubsystemType::WindowsCeGui:return "Windows CE GUI";
		case SubsystemType::EfiApplication:return "EFI Application";
		case SubsystemType::EfiBootServiceDriver:return "EFI Boot Service Driver";
		case SubsystemType::EfiRuntimeDriver:return "EFI Runtime Driver";
		case SubsystemType::EfiRom:return "EFI Rom Image";
		case SubsystemType::Xbox:return "XBox";
		case SubsystemType::WindowsBootApplication:return "Windows boot application";
		default: return "NOT FOUND SUBSYSTEM TYPE";
	}
}

auto POEX::ImageOptionalHeader::DataDirectory() -> std::vector<std::unique_ptr<ImageDataDirectory>>
{
	std::vector<std::unique_ptr<ImageDataDirectory>> dDirectory;
	for (unsigned int i = 0; i < 16; i++)
	{
		if (this->is64Bit)
		{
			dDirectory.push_back(std::unique_ptr<ImageDataDirectory> 
				(new ImageDataDirectory(this->bFile, this->offset + 0x0070 + i * 0x0008, DataDirectoryType(i))));
		}
		else
		{
			dDirectory.push_back(std::unique_ptr<ImageDataDirectory>
				(new ImageDataDirectory(this->bFile, this->offset + 0x0060 + i * 0x0008, DataDirectoryType(i))));
		}
	}

	return dDirectory;
}

auto POEX::ImageOptionalHeader::Magic() const -> FileType
{
	return (FileType)this->bFile->ReadUnsignedShort(this->offset + 0x0000);
}

auto POEX::ImageOptionalHeader::Magic(const FileType& fileType) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0000, (unsigned short)fileType);
}

auto POEX::ImageOptionalHeader::MajorLinkerVersion() const -> byte
{
	return this->bFile->ReadByte(this->offset + 0x0002);
}

auto POEX::ImageOptionalHeader::MajorLinkerVersion(const byte& mlVersion)
{
	this->bFile->WriteByte(this->offset + 0x0002, mlVersion);
}

auto POEX::ImageOptionalHeader::MinorLinkerVersion() const -> byte
{
	return this->bFile->ReadByte(this->offset + 0x0003);
}

auto POEX::ImageOptionalHeader::MinorLinkerVersion(const byte& mlVersion)
{
	this->bFile->WriteByte(this->offset + 0x0003, mlVersion);
}

auto POEX::ImageOptionalHeader::SizeOfCode() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0004);
}

auto POEX::ImageOptionalHeader::SizeOfCode(const unsigned int& sizeOfCode) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0004, sizeOfCode);
}

auto POEX::ImageOptionalHeader::SizeOfInitializedData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0008);
}

auto POEX::ImageOptionalHeader::SizeOfInitializedData(const unsigned int& sizeOfInitializedData) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0008, sizeOfInitializedData);
}

auto POEX::ImageOptionalHeader::SizeOfUninitializedData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x000C);
}

auto POEX::ImageOptionalHeader::SizeOfUninitializedData(const unsigned int& sizeOfUninitializedData) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x000C, sizeOfUninitializedData);
}

auto POEX::ImageOptionalHeader::AddressOfEntryPoint() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0010);
}

auto POEX::ImageOptionalHeader::AddressOfEntryPoint(const unsigned int& addressOfEntryPoint) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0010, addressOfEntryPoint);
}

auto POEX::ImageOptionalHeader::BaseOfCode() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0014);
}

auto POEX::ImageOptionalHeader::BaseOfCode(const unsigned int& baseOfCode) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0014, baseOfCode);
}

auto POEX::ImageOptionalHeader::BaseOfData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0018);
}

auto POEX::ImageOptionalHeader::BaseOfData(const unsigned int& baseOfData) -> void
{
	if (!this->is64Bit) // if it's 32 bit
		this->bFile->WriteUnsignedInt(this->offset + 0x0018, baseOfData);
	else
		THROW_EXCEPTION("[ERROR] OptionalHeader->BaseOfData does not exist in 64 bit applications.");
}

auto POEX::ImageOptionalHeader::ImageBase() const -> unsigned long
{
	return this->is64Bit ? this->bFile->ReadUnsignedLong(this->offset + 0x0018) : this->bFile->ReadUnsignedInt(this->offset + 0x001C);
}

auto POEX::ImageOptionalHeader::ImageBase(const unsigned long& imageBase) -> void
{
	this->is64Bit ? this->bFile->WriteUnsignedLong(this->offset + 0x0018, imageBase) : this->bFile->WriteUnsignedInt(this->offset + 0x001C, unsigned int(imageBase));
}

auto POEX::ImageOptionalHeader::SectionAlignment() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0020);
}

auto POEX::ImageOptionalHeader::SectionAlignment(const unsigned int& sectionAlignment) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0020, sectionAlignment);
}

auto POEX::ImageOptionalHeader::FileAlignment() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0024);
}

auto POEX::ImageOptionalHeader::FileAlignment(const unsigned int& fileAlignment) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0024, fileAlignment);
}

auto POEX::ImageOptionalHeader::MajorOperatingSystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0028);
}

auto POEX::ImageOptionalHeader::MajorOperatingSystemVersion(const unsigned short& majorOperatingSystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0028, majorOperatingSystemVersion);
}

auto POEX::ImageOptionalHeader::MinorOperatingSystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x002A);
}

auto POEX::ImageOptionalHeader::MinorOperatingSystemVersion(const unsigned short& minorOperatingSystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x002A, minorOperatingSystemVersion);
}

auto POEX::ImageOptionalHeader::MajorImageVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x002C);
}

auto POEX::ImageOptionalHeader::MajorImageVersion(const unsigned short& majorImageVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x002C, majorImageVersion);
}

auto POEX::ImageOptionalHeader::MinorImageVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x002E);
}

auto POEX::ImageOptionalHeader::MinorImageVersion(const unsigned short& minorImageVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x002E, minorImageVersion);
}

auto POEX::ImageOptionalHeader::MajorSubsystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0030);
}

auto POEX::ImageOptionalHeader::MajorSubsystemVersion(const unsigned short& majorSubsystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0030, majorSubsystemVersion);
}

auto POEX::ImageOptionalHeader::MinorSubsystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0032);
}

auto POEX::ImageOptionalHeader::MinorSubsystemVersion(const unsigned short& minorSubsystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0032, minorSubsystemVersion);
}

auto POEX::ImageOptionalHeader::Win32VersionValue() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0034);
}

auto POEX::ImageOptionalHeader::Win32VersionValue(const unsigned int& win32VersionValue) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0034, win32VersionValue);
}

auto POEX::ImageOptionalHeader::SizeOfImage() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0038);
}

auto POEX::ImageOptionalHeader::SizeOfImage(const unsigned int& sizeOfImage) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0038, sizeOfImage);
}

auto POEX::ImageOptionalHeader::SizeOfHeaders() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x003C);
}

auto POEX::ImageOptionalHeader::SizeOfHeaders(const unsigned int& sizeOfHeaders) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x003C, sizeOfHeaders);
}

auto POEX::ImageOptionalHeader::CheckSum() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0040);
}

auto POEX::ImageOptionalHeader::CheckSum(const unsigned int& checkSum) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0040, checkSum);
}

auto POEX::ImageOptionalHeader::Subsystem() const -> SubsystemType
{
	return (SubsystemType)this->bFile->ReadUnsignedShort(this->offset + 0x0044);
}

auto POEX::ImageOptionalHeader::Subsystem(const SubsystemType& systemType) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0044, (unsigned short)systemType);
}

auto POEX::ImageOptionalHeader::DllCharacteristics() const -> DllCharacteristicsType
{
	return (DllCharacteristicsType)this->bFile->ReadUnsignedShort(this->offset + 0x0046);
}

auto POEX::ImageOptionalHeader::DllCharacteristics(const DllCharacteristicsType& dllCharacteristicsType) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0046, (unsigned short)dllCharacteristicsType);
}

auto POEX::ImageOptionalHeader::SizeOfStackReserve() const -> unsigned long
{
	return this->is64Bit 
		? this->bFile->ReadUnsignedLong(this->offset + 0x0048) 
		: this->bFile->ReadUnsignedInt(this->offset + 0x0048);
}

auto POEX::ImageOptionalHeader::SizeOfStackReserve(const unsigned long& sizeOfStackReserve) -> void
{
	this->is64Bit 
		? this->bFile->WriteUnsignedLong(this->offset + 0x0048, sizeOfStackReserve) 
		: this->bFile->WriteUnsignedInt(this->offset + 0x0048, (unsigned int)sizeOfStackReserve);
}

auto POEX::ImageOptionalHeader::SizeOfStackCommit() const -> unsigned long
{
	return this->is64Bit 
		? this->bFile->ReadUnsignedLong(this->offset + 0x0050) 
		: this->bFile->ReadUnsignedInt(this->offset + 0x004C);
}

auto POEX::ImageOptionalHeader::SizeOfStackCommit(const unsigned long& sizeOfStackCommit) -> void
{
	this->is64Bit 
		? this->bFile->WriteUnsignedLong(this->offset + 0x0050, sizeOfStackCommit) 
		: this->bFile->WriteUnsignedInt(this->offset + 0x004C, (unsigned int)sizeOfStackCommit);
}

auto POEX::ImageOptionalHeader::SizeOfHeapReserve() const -> unsigned long
{
	return this->is64Bit
		? this->bFile->ReadUnsignedLong(this->offset + 0x0058)
		: this->bFile->ReadUnsignedInt(this->offset + 0x0050);
}

auto POEX::ImageOptionalHeader::SizeOfHeapReserve(const unsigned long& sizeOfHeapReserve) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedLong(this->offset + 0x0058, sizeOfHeapReserve)
		: this->bFile->WriteUnsignedInt(this->offset + 0x0050, (unsigned int)sizeOfHeapReserve);
}

auto POEX::ImageOptionalHeader::SizeOfHeapCommit() const -> unsigned long
{
	return this->is64Bit
		? this->bFile->ReadUnsignedLong(this->offset + 0x0060)
		: this->bFile->ReadUnsignedInt(this->offset + 0x0054);
}

auto POEX::ImageOptionalHeader::SizeOfHeapCommit(const unsigned long& sizeOfHeapCommit) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedLong(this->offset + 0x0060, sizeOfHeapCommit)
		: this->bFile->WriteUnsignedInt(this->offset + 0x0054, (unsigned int)sizeOfHeapCommit);
}

auto POEX::ImageOptionalHeader::LoaderFlags() const -> unsigned int
{
	return this->is64Bit
		? this->bFile->ReadUnsignedInt(this->offset + 0x0068)
		: this->bFile->ReadUnsignedInt(this->offset + 0x0058);
}

auto POEX::ImageOptionalHeader::LoaderFlags(const unsigned int& loaderFlags) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedInt(this->offset + 0x0068, loaderFlags)
		: this->bFile->WriteUnsignedInt(this->offset + 0x0058, (unsigned int)loaderFlags);
}

auto POEX::ImageOptionalHeader::NumberOfRvaAndSizes() const -> unsigned int
{
	return this->is64Bit
		? this->bFile->ReadUnsignedInt(this->offset + 0x006C)
		: this->bFile->ReadUnsignedInt(this->offset + 0x005C);
}

auto POEX::ImageOptionalHeader::NumberOfRvaAndSizes(const unsigned int& numberOfRvaAndSizes) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedInt(this->offset + 0x006C, numberOfRvaAndSizes)
		: this->bFile->WriteUnsignedInt(this->offset + 0x005C, numberOfRvaAndSizes);
}