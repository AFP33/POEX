#include "../Headers/ImageOptionalHeader.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageOptionalHeader::ImageOptionalHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, 
	const bool& is64Bit) : bFile(bFile), offset(offset), is64Bit(is64Bit)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageOptionalHeader::ToString(SubsystemType subsystem) -> std::string
{
	try
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
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::ToString(DllCharacteristicsType dllCharacteristicsType) -> std::string
{
	try
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
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::ToString(FileType fileType) -> std::string
{
	try
	{
		switch (fileType)
		{
		case FileType::BIT32: return "File is 32bit.";
		case FileType::BIT64: return "File is 64bit.";
		case FileType::ROM: return "File is ROM.";
		default: return "NOT FOUND FILE TYPE";
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::DataDirectory() -> std::vector<std::unique_ptr<ImageDataDirectory>>
{
	try
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
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::Magic() const -> FileType
{
	try
	{
		return (FileType)this->bFile->ReadUnsignedShort(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::Magic(const FileType& fileType) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0000, (unsigned short)fileType);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorLinkerVersion() const -> byte
{
	try
	{
		return this->bFile->ReadByte(this->offset + 0x0002);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorLinkerVersion(const byte& mlVersion)
{
	try
	{
		this->bFile->WriteByte(this->offset + 0x0002, mlVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorLinkerVersion() const -> byte
{
	try
	{
		return this->bFile->ReadByte(this->offset + 0x0003);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorLinkerVersion(const byte& mlVersion)
{
	try
	{
		this->bFile->WriteByte(this->offset + 0x0003, mlVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfCode() const -> unsigned int
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

auto ImageOptionalHeader::SizeOfCode(const unsigned int& sizeOfCode) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, sizeOfCode);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfInitializedData() const -> unsigned int
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

auto ImageOptionalHeader::SizeOfInitializedData(const unsigned int& sizeOfInitializedData) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0008, sizeOfInitializedData);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfUninitializedData() const -> unsigned int
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

auto ImageOptionalHeader::SizeOfUninitializedData(const unsigned int& sizeOfUninitializedData) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000C, sizeOfUninitializedData);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::AddressOfEntryPoint() const -> unsigned int
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

auto ImageOptionalHeader::AddressOfEntryPoint(const unsigned int& addressOfEntryPoint) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0010, addressOfEntryPoint);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::BaseOfCode() const -> unsigned int
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

auto ImageOptionalHeader::BaseOfCode(const unsigned int& baseOfCode) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0014, baseOfCode);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::BaseOfData() const -> unsigned int
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

auto ImageOptionalHeader::BaseOfData(const unsigned int& baseOfData) -> void
{
	try
	{
		if (!this->is64Bit) // if it's 32 bit
			this->bFile->WriteUnsignedInt(this->offset + 0x0018, baseOfData);
		else
			THROW_EXCEPTION("[ERROR] OptionalHeader->BaseOfData does not exist in 64 bit applications.");
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::ImageBase() const -> unsigned long
{
	try
	{
		return this->is64Bit ?
			this->bFile->ReadUnsignedLong(this->offset + 0x0018) :
			this->bFile->ReadUnsignedInt(this->offset + 0x001C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::ImageBase(const unsigned long& imageBase) -> void
{
	try
	{
		this->is64Bit ?
			this->bFile->WriteUnsignedLong(this->offset + 0x0018, imageBase) :
			this->bFile->WriteUnsignedInt(this->offset + 0x001C, unsigned int(imageBase));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SectionAlignment() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0020);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SectionAlignment(const unsigned int& sectionAlignment) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0020, sectionAlignment);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::FileAlignment() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0024);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::FileAlignment(const unsigned int& fileAlignment) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0024, fileAlignment);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorOperatingSystemVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0028);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorOperatingSystemVersion(const unsigned short& majorOperatingSystemVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0028, majorOperatingSystemVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorOperatingSystemVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x002A);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorOperatingSystemVersion(const unsigned short& minorOperatingSystemVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x002A, minorOperatingSystemVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorImageVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x002C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorImageVersion(const unsigned short& majorImageVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x002C, majorImageVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorImageVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x002E);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorImageVersion(const unsigned short& minorImageVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x002E, minorImageVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorSubsystemVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0030);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MajorSubsystemVersion(const unsigned short& majorSubsystemVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0030, majorSubsystemVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorSubsystemVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0032);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::MinorSubsystemVersion(const unsigned short& minorSubsystemVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0032, minorSubsystemVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::Win32VersionValue() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0034);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::Win32VersionValue(const unsigned int& win32VersionValue) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0034, win32VersionValue);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfImage() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0038);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfImage(const unsigned int& sizeOfImage) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0038, sizeOfImage);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfHeaders() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x003C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfHeaders(const unsigned int& sizeOfHeaders) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x003C, sizeOfHeaders);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::CheckSum() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0040);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::CheckSum(const unsigned int& checkSum) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0040, checkSum);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::Subsystem() const -> SubsystemType
{
	try
	{
		return (SubsystemType)this->bFile->ReadUnsignedShort(this->offset + 0x0044);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::Subsystem(const SubsystemType& systemType) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0044, (unsigned short)systemType);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::DllCharacteristics() const -> DllCharacteristicsType
{
	try
	{
		return (DllCharacteristicsType)this->bFile->ReadUnsignedShort(this->offset + 0x0046);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::DllCharacteristics(const DllCharacteristicsType& dllCharacteristicsType) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0046, (unsigned short)dllCharacteristicsType);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfStackReserve() const -> unsigned long
{
	try
	{
		return this->is64Bit
			? this->bFile->ReadUnsignedLong(this->offset + 0x0048)
			: this->bFile->ReadUnsignedInt(this->offset + 0x0048);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfStackReserve(const unsigned long& sizeOfStackReserve) -> void
{
	try
	{
		this->is64Bit
			? this->bFile->WriteUnsignedLong(this->offset + 0x0048, sizeOfStackReserve)
			: this->bFile->WriteUnsignedInt(this->offset + 0x0048, (unsigned int)sizeOfStackReserve);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfStackCommit() const -> unsigned long
{
	try
	{
		return this->is64Bit
			? this->bFile->ReadUnsignedLong(this->offset + 0x0050)
			: this->bFile->ReadUnsignedInt(this->offset + 0x004C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfStackCommit(const unsigned long& sizeOfStackCommit) -> void
{
	try
	{
		this->is64Bit
			? this->bFile->WriteUnsignedLong(this->offset + 0x0050, sizeOfStackCommit)
			: this->bFile->WriteUnsignedInt(this->offset + 0x004C, (unsigned int)sizeOfStackCommit);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfHeapReserve() const -> unsigned long
{
	try
	{
		return this->is64Bit
			? this->bFile->ReadUnsignedLong(this->offset + 0x0058)
			: this->bFile->ReadUnsignedInt(this->offset + 0x0050);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfHeapReserve(const unsigned long& sizeOfHeapReserve) -> void
{
	try
	{
		this->is64Bit
			? this->bFile->WriteUnsignedLong(this->offset + 0x0058, sizeOfHeapReserve)
			: this->bFile->WriteUnsignedInt(this->offset + 0x0050, (unsigned int)sizeOfHeapReserve);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfHeapCommit() const -> unsigned long
{
	try
	{
		return this->is64Bit
			? this->bFile->ReadUnsignedLong(this->offset + 0x0060)
			: this->bFile->ReadUnsignedInt(this->offset + 0x0054);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::SizeOfHeapCommit(const unsigned long& sizeOfHeapCommit) -> void
{
	try
	{
		this->is64Bit
			? this->bFile->WriteUnsignedLong(this->offset + 0x0060, sizeOfHeapCommit)
			: this->bFile->WriteUnsignedInt(this->offset + 0x0054, (unsigned int)sizeOfHeapCommit);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::LoaderFlags() const -> unsigned int
{
	try
	{
		return this->is64Bit
			? this->bFile->ReadUnsignedInt(this->offset + 0x0068)
			: this->bFile->ReadUnsignedInt(this->offset + 0x0058);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::LoaderFlags(const unsigned int& loaderFlags) -> void
{
	try
	{
		this->is64Bit
			? this->bFile->WriteUnsignedInt(this->offset + 0x0068, loaderFlags)
			: this->bFile->WriteUnsignedInt(this->offset + 0x0058, (unsigned int)loaderFlags);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::NumberOfRvaAndSizes() const -> unsigned int
{
	try
	{
		return this->is64Bit
			? this->bFile->ReadUnsignedInt(this->offset + 0x006C)
			: this->bFile->ReadUnsignedInt(this->offset + 0x005C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageOptionalHeader::NumberOfRvaAndSizes(const unsigned int& numberOfRvaAndSizes) -> void
{
	try
	{
		this->is64Bit
			? this->bFile->WriteUnsignedInt(this->offset + 0x006C, numberOfRvaAndSizes)
			: this->bFile->WriteUnsignedInt(this->offset + 0x005C, numberOfRvaAndSizes);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}