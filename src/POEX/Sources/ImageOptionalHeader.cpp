#include "../Headers/ImageOptionalHeader.h"

ImageOptionalHeader::ImageOptionalHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, 
	const bool& is64Bit) : bFile(bFile), offset(offset), is64Bit(is64Bit)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageOptionalHeader::ToString(SubsystemType subsystem) -> std::string
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

auto ImageOptionalHeader::ToString(DllCharacteristicsType dllCharacteristicsType) -> std::string
{
	switch (dllCharacteristicsType)
	{
		case DllCharacteristicsType::HighEntropyVA: return "Image can handle a high entropy 64-bit virtual address space.";
		case DllCharacteristicsType::DynamicBase: return "DLL can be relocated at load time.";
		case DllCharacteristicsType::ForceIntegrity: return "Code Integrity checks are enforced.";
		case DllCharacteristicsType::NxCompat: return "Image is NX compatible.";
		case DllCharacteristicsType::NoIsolation: return "Isolation aware, but do not isolate the image.";
		case DllCharacteristicsType::NoSeh: return "Does not use structured exception (SE) handling. No SE handler may be called in this image.";
		case DllCharacteristicsType::NoBind: return "Do not bind the image.";
		case DllCharacteristicsType::AppContainer: return "Image must execute in an AppContainer.";
		case DllCharacteristicsType::WdmDriver: return "A WDM driver.";
		case DllCharacteristicsType::GuardCF: return "Image supports Control Flow Guard.";
		case DllCharacteristicsType::TerminalServerAware: return "Terminal Server aware.";
		default: return "NOT FOUND DllCharacteristicsType";
	}
}

auto ImageOptionalHeader::ToString(FileType fileType) -> std::string
{
	switch (fileType)
	{
		case FileType::BIT32: return "File is 32bit.";
		case FileType::BIT64: return "File is 64bit.";
		case FileType::ROM: return "File is ROM.";
		default: return "NOT FOUND FILE TYPE";
	}
}

auto ImageOptionalHeader::DataDirectory() -> std::vector<std::unique_ptr<ImageDataDirectory>>
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

auto ImageOptionalHeader::Magic() const -> FileType
{
	return (FileType)this->bFile->ReadUnsignedShort(this->offset + 0x0000);
}

auto ImageOptionalHeader::Magic(const FileType& fileType) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0000, (unsigned short)fileType);
}

auto ImageOptionalHeader::MajorLinkerVersion() const -> byte
{
	return this->bFile->ReadByte(this->offset + 0x0002);
}

auto ImageOptionalHeader::MajorLinkerVersion(const byte& mlVersion)
{
	this->bFile->WriteByte(this->offset + 0x0002, mlVersion);
}

auto ImageOptionalHeader::MinorLinkerVersion() const -> byte
{
	return this->bFile->ReadByte(this->offset + 0x0003);
}

auto ImageOptionalHeader::MinorLinkerVersion(const byte& mlVersion)
{
	this->bFile->WriteByte(this->offset + 0x0003, mlVersion);
}

auto ImageOptionalHeader::SizeOfCode() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0004);
}

auto ImageOptionalHeader::SizeOfCode(const unsigned int& sizeOfCode) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0004, sizeOfCode);
}

auto ImageOptionalHeader::SizeOfInitializedData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0008);
}

auto ImageOptionalHeader::SizeOfInitializedData(const unsigned int& sizeOfInitializedData) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0008, sizeOfInitializedData);
}

auto ImageOptionalHeader::SizeOfUninitializedData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x000C);
}

auto ImageOptionalHeader::SizeOfUninitializedData(const unsigned int& sizeOfUninitializedData) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x000C, sizeOfUninitializedData);
}

auto ImageOptionalHeader::AddressOfEntryPoint() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0010);
}

auto ImageOptionalHeader::AddressOfEntryPoint(const unsigned int& addressOfEntryPoint) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0010, addressOfEntryPoint);
}

auto ImageOptionalHeader::BaseOfCode() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0014);
}

auto ImageOptionalHeader::BaseOfCode(const unsigned int& baseOfCode) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0014, baseOfCode);
}

auto ImageOptionalHeader::BaseOfData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0018);
}

auto ImageOptionalHeader::BaseOfData(const unsigned int& baseOfData) -> void
{
	if (!this->is64Bit) // if it's 32 bit
		this->bFile->WriteUnsignedInt(this->offset + 0x0018, baseOfData);
	else
		THROW_EXCEPTION("[ERROR] OptionalHeader->BaseOfData does not exist in 64 bit applications.");
}

auto ImageOptionalHeader::ImageBase() const -> unsigned long
{
	return this->is64Bit ? this->bFile->ReadUnsignedLong(this->offset + 0x0018) : this->bFile->ReadUnsignedInt(this->offset + 0x001C);
}

auto ImageOptionalHeader::ImageBase(const unsigned long& imageBase) -> void
{
	this->is64Bit ? this->bFile->WriteUnsignedLong(this->offset + 0x0018, imageBase) : this->bFile->WriteUnsignedInt(this->offset + 0x001C, unsigned int(imageBase));
}

auto ImageOptionalHeader::SectionAlignment() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0020);
}

auto ImageOptionalHeader::SectionAlignment(const unsigned int& sectionAlignment) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0020, sectionAlignment);
}

auto ImageOptionalHeader::FileAlignment() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0024);
}

auto ImageOptionalHeader::FileAlignment(const unsigned int& fileAlignment) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0024, fileAlignment);
}

auto ImageOptionalHeader::MajorOperatingSystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0028);
}

auto ImageOptionalHeader::MajorOperatingSystemVersion(const unsigned short& majorOperatingSystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0028, majorOperatingSystemVersion);
}

auto ImageOptionalHeader::MinorOperatingSystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x002A);
}

auto ImageOptionalHeader::MinorOperatingSystemVersion(const unsigned short& minorOperatingSystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x002A, minorOperatingSystemVersion);
}

auto ImageOptionalHeader::MajorImageVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x002C);
}

auto ImageOptionalHeader::MajorImageVersion(const unsigned short& majorImageVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x002C, majorImageVersion);
}

auto ImageOptionalHeader::MinorImageVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x002E);
}

auto ImageOptionalHeader::MinorImageVersion(const unsigned short& minorImageVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x002E, minorImageVersion);
}

auto ImageOptionalHeader::MajorSubsystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0030);
}

auto ImageOptionalHeader::MajorSubsystemVersion(const unsigned short& majorSubsystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0030, majorSubsystemVersion);
}

auto ImageOptionalHeader::MinorSubsystemVersion() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0032);
}

auto ImageOptionalHeader::MinorSubsystemVersion(const unsigned short& minorSubsystemVersion) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0032, minorSubsystemVersion);
}

auto ImageOptionalHeader::Win32VersionValue() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0034);
}

auto ImageOptionalHeader::Win32VersionValue(const unsigned int& win32VersionValue) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0034, win32VersionValue);
}

auto ImageOptionalHeader::SizeOfImage() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0038);
}

auto ImageOptionalHeader::SizeOfImage(const unsigned int& sizeOfImage) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0038, sizeOfImage);
}

auto ImageOptionalHeader::SizeOfHeaders() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x003C);
}

auto ImageOptionalHeader::SizeOfHeaders(const unsigned int& sizeOfHeaders) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x003C, sizeOfHeaders);
}

auto ImageOptionalHeader::CheckSum() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0040);
}

auto ImageOptionalHeader::CheckSum(const unsigned int& checkSum) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0040, checkSum);
}

auto ImageOptionalHeader::Subsystem() const -> SubsystemType
{
	return (SubsystemType)this->bFile->ReadUnsignedShort(this->offset + 0x0044);
}

auto ImageOptionalHeader::Subsystem(const SubsystemType& systemType) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0044, (unsigned short)systemType);
}

auto ImageOptionalHeader::DllCharacteristics() const -> DllCharacteristicsType
{
	return (DllCharacteristicsType)this->bFile->ReadUnsignedShort(this->offset + 0x0046);
}

auto ImageOptionalHeader::DllCharacteristics(const DllCharacteristicsType& dllCharacteristicsType) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0046, (unsigned short)dllCharacteristicsType);
}

auto ImageOptionalHeader::SizeOfStackReserve() const -> unsigned long
{
	return this->is64Bit 
		? this->bFile->ReadUnsignedLong(this->offset + 0x0048) 
		: this->bFile->ReadUnsignedInt(this->offset + 0x0048);
}

auto ImageOptionalHeader::SizeOfStackReserve(const unsigned long& sizeOfStackReserve) -> void
{
	this->is64Bit 
		? this->bFile->WriteUnsignedLong(this->offset + 0x0048, sizeOfStackReserve) 
		: this->bFile->WriteUnsignedInt(this->offset + 0x0048, (unsigned int)sizeOfStackReserve);
}

auto ImageOptionalHeader::SizeOfStackCommit() const -> unsigned long
{
	return this->is64Bit 
		? this->bFile->ReadUnsignedLong(this->offset + 0x0050) 
		: this->bFile->ReadUnsignedInt(this->offset + 0x004C);
}

auto ImageOptionalHeader::SizeOfStackCommit(const unsigned long& sizeOfStackCommit) -> void
{
	this->is64Bit 
		? this->bFile->WriteUnsignedLong(this->offset + 0x0050, sizeOfStackCommit) 
		: this->bFile->WriteUnsignedInt(this->offset + 0x004C, (unsigned int)sizeOfStackCommit);
}

auto ImageOptionalHeader::SizeOfHeapReserve() const -> unsigned long
{
	return this->is64Bit
		? this->bFile->ReadUnsignedLong(this->offset + 0x0058)
		: this->bFile->ReadUnsignedInt(this->offset + 0x0050);
}

auto ImageOptionalHeader::SizeOfHeapReserve(const unsigned long& sizeOfHeapReserve) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedLong(this->offset + 0x0058, sizeOfHeapReserve)
		: this->bFile->WriteUnsignedInt(this->offset + 0x0050, (unsigned int)sizeOfHeapReserve);
}

auto ImageOptionalHeader::SizeOfHeapCommit() const -> unsigned long
{
	return this->is64Bit
		? this->bFile->ReadUnsignedLong(this->offset + 0x0060)
		: this->bFile->ReadUnsignedInt(this->offset + 0x0054);
}

auto ImageOptionalHeader::SizeOfHeapCommit(const unsigned long& sizeOfHeapCommit) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedLong(this->offset + 0x0060, sizeOfHeapCommit)
		: this->bFile->WriteUnsignedInt(this->offset + 0x0054, (unsigned int)sizeOfHeapCommit);
}

auto ImageOptionalHeader::LoaderFlags() const -> unsigned int
{
	return this->is64Bit
		? this->bFile->ReadUnsignedInt(this->offset + 0x0068)
		: this->bFile->ReadUnsignedInt(this->offset + 0x0058);
}

auto ImageOptionalHeader::LoaderFlags(const unsigned int& loaderFlags) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedInt(this->offset + 0x0068, loaderFlags)
		: this->bFile->WriteUnsignedInt(this->offset + 0x0058, (unsigned int)loaderFlags);
}

auto ImageOptionalHeader::NumberOfRvaAndSizes() const -> unsigned int
{
	return this->is64Bit
		? this->bFile->ReadUnsignedInt(this->offset + 0x006C)
		: this->bFile->ReadUnsignedInt(this->offset + 0x005C);
}

auto ImageOptionalHeader::NumberOfRvaAndSizes(const unsigned int& numberOfRvaAndSizes) -> void
{
	this->is64Bit
		? this->bFile->WriteUnsignedInt(this->offset + 0x006C, numberOfRvaAndSizes)
		: this->bFile->WriteUnsignedInt(this->offset + 0x005C, numberOfRvaAndSizes);
}