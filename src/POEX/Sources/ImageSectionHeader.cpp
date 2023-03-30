#include "..\Headers\ImageSectionHeader.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageSectionHeader::ImageSectionHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, 
	const unsigned long& imageBaseAddress) : bFile(bFile), offset(offset), imageBaseAddress(imageBaseAddress)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageSectionHeader::ToString(SectionFlag sectionFlag) -> std::string
{
	try
	{
		switch (sectionFlag)
		{
		case SectionFlag::TypeNoPad: return "The section should not be padded to the next boundary. This flag is obsolete and is replaced by IMAGE_SCN_ALIGN_1BYTES. This is valid only for object files.";
		case SectionFlag::CntCode: return "The section contains executable code.";
		case SectionFlag::CntInitializedData: return "The section contains initialized data.";
		case SectionFlag::CntUninitializedData: return "The section contains uninitialized data.";
		case SectionFlag::LnkOther: return "Reserved for future use.";
		case SectionFlag::LnkInfo: return "The section contains comments or other information.";
		case SectionFlag::LnkRemove: return "The section will not become part of the image. This is valid only for object files.";
		case SectionFlag::LnkComdat: return "The section contains COMDAT data.";
		case SectionFlag::NoDeferSpecExc: return "Unknown.";
		case SectionFlag::Gprel: return "The section contains data referenced through the global pointer (GP).";
		case SectionFlag::MemPurgeable: return "Reserved for future use.";
		case SectionFlag::MemLocked: return "Reserved for future use.";
		case SectionFlag::MemPreload: return "Reserved for future use.";
		case SectionFlag::Align1Bytes: return "Align data on a 1-byte boundary. Valid only for object files.";
		case SectionFlag::Align2Bytes: return "Align data on a 2-byte boundary. Valid only for object files.";
		case SectionFlag::Align4Bytes: return "Align data on a 4-byte boundary. Valid only for object files.";
		case SectionFlag::Align8Bytes: return "Align data on a 8-byte boundary. Valid only for object files.";
		case SectionFlag::Align16Bytes: return "Align data on a 16-byte boundary. Valid only for object files.";
		case SectionFlag::Align32Bytes: return "Align data on a 32-byte boundary. Valid only for object files.";
		case SectionFlag::Align64Bytes: return "Align data on a 64-byte boundary. Valid only for object files.";
		case SectionFlag::Align128Bytes: return "Align data on a 128-byte boundary. Valid only for object files.";
		case SectionFlag::Align256Bytes: return "Align data on a 256-byte boundary. Valid only for object files.";
		case SectionFlag::Align512Bytes: return "Align data on a 512-byte boundary. Valid only for object files.";
		case SectionFlag::Align1024Bytes: return "Align data on a 1024-byte boundary. Valid only for object files.";
		case SectionFlag::Align2048Bytes: return "Align data on a 2048-byte boundary. Valid only for object files.";
		case SectionFlag::Align4096Bytes: return "Align data on a 4096-byte boundary. Valid only for object files.";
		case SectionFlag::Align8192Bytes: return "Align data on a 8192-byte boundary. Valid only for object files.";
		case SectionFlag::AlignMask: return "";
		case SectionFlag::LnkNrelocOvfl: return "The section contains extended relocations.";
		case SectionFlag::MemDiscardable: return "The section can be discarded as needed.";
		case SectionFlag::MemNotCached: return "The section cannot be cached.";
		case SectionFlag::MemNotPaged: return "The section is not pageable.";
		case SectionFlag::MemShared: return "The section can be shared in memory.";
		case SectionFlag::MemExecute: return "The section can be executed as code.";
		case SectionFlag::MemRead: return "The section can be read.";
		case SectionFlag::MemWrite: return "The section can be written to.";
		default: return "NOT FOUND SectionFlag.";
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::ImageBaseAddress() -> unsigned long
{
	return this->imageBaseAddress;
}

auto ImageSectionHeader::Name() const -> std::string
{
	try
	{
		auto nameArr = bFile->SubArray(this->offset, 8);
		return std::string(nameArr.begin(), nameArr.end());
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::Name(const std::string& name) -> void
{
	if (name.empty())
		THROW_OUT_OF_RANGE("[ERROR] 'name' cannot be empty.");
	auto nameArr = FixedNameLength(name);
	this->bFile->WriteBytes(this->offset, nameArr);
}

auto ImageSectionHeader::VirtualSize() const -> unsigned int
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

auto ImageSectionHeader::VirtualSize(const unsigned int& virtualSize) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0008, virtualSize);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::VirtualAddress() const -> unsigned int
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

auto ImageSectionHeader::VirtualAddress(const unsigned int& virtualAddress) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000C, virtualAddress);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::SizeOfRawData() const -> unsigned int
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

auto ImageSectionHeader::SizeOfRawData(const unsigned int& sizeOfRawData) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0010, sizeOfRawData);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::PointerToRawData() const -> unsigned int
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

auto ImageSectionHeader::PointerToRawData(const unsigned int& pointerToRawData) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0014, pointerToRawData);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::PointerToRelocations() const -> unsigned int
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

auto ImageSectionHeader::PointerToRelocations(const unsigned int& pointerToRelocations) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0018, pointerToRelocations);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::PointerToLinenumbers() const -> unsigned int
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

auto ImageSectionHeader::PointerToLinenumbers(const unsigned int& pointerToLinenumbers) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x001C, pointerToLinenumbers);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::NumberOfRelocations() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0020);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::NumberOfRelocations(const unsigned short& numberOfRelocations) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0020, numberOfRelocations);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::NumberOfLinenumbers() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0022);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::NumberOfLinenumbers(const unsigned short& numberOfLinenumbers) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0022, numberOfLinenumbers);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::Characteristics() const -> SectionFlag
{
	try
	{
		return SectionFlag(this->bFile->ReadUnsignedInt(this->offset + 0x0024));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::Characteristics(const SectionFlag& characteristics) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0024, (unsigned int)characteristics);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::ToArray() -> std::vector<byte>
{
	try
	{
		auto header = std::vector<byte>();
		header.reserve(SECTION_HEADER_SIZE); // Section header size is 40 bytes

		auto name = this->FixedNameLength(this->Name());
		auto virtualSize = this->bFile->ToBytesArray(this->VirtualSize());
		auto virtualAddress = this->bFile->ToBytesArray(this->VirtualAddress());
		auto sizeOfRawData = this->bFile->ToBytesArray(this->SizeOfRawData());
		auto pointerToRawData = this->bFile->ToBytesArray(this->PointerToRawData());
		auto pointerToRelocations = this->bFile->ToBytesArray(this->PointerToRelocations());
		auto pointerToLinenumbers = this->bFile->ToBytesArray(this->PointerToLinenumbers());
		auto numberOfRelocations = this->bFile->ToBytesArray(this->NumberOfRelocations());
		auto numberOfLinenumbers = this->bFile->ToBytesArray(this->NumberOfLinenumbers());
		auto characteristics = this->bFile->ToBytesArray((unsigned int)this->Characteristics());

		header.insert(header.end(), name.begin(), name.end());
		header.insert(header.end(), virtualSize.begin(), virtualSize.end());
		header.insert(header.end(), virtualAddress.begin(), virtualAddress.end());
		header.insert(header.end(), sizeOfRawData.begin(), sizeOfRawData.end());
		header.insert(header.end(), pointerToRawData.begin(), pointerToRawData.end());
		header.insert(header.end(), pointerToRelocations.begin(), pointerToRelocations.end());
		header.insert(header.end(), pointerToLinenumbers.begin(), pointerToLinenumbers.end());
		header.insert(header.end(), numberOfRelocations.begin(), numberOfRelocations.end());
		header.insert(header.end(), numberOfLinenumbers.begin(), numberOfLinenumbers.end());
		header.insert(header.end(), characteristics.begin(), characteristics.end());

		return header;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageSectionHeader::FixedNameLength(const std::string& name) -> std::vector<byte>
{
	try
	{
		auto nameArr = std::vector<byte>(name.begin(), name.end());
		if (nameArr.size() > 8)
			THROW_OUT_OF_RANGE("[ERROR] 'name' length is too long.");
		while (nameArr.size() < 8)
			nameArr.push_back((byte)0);

		return nameArr;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
