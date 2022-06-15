#include "..\Headers\ImageSectionHeader.h"

POEX::ImageSectionHeader::ImageSectionHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, 
	const unsigned long& imageBaseAddress) : bFile(bFile), offset(offset), imageBaseAddress(imageBaseAddress)
{
}

auto POEX::ImageSectionHeader::ImageBaseAddress() -> unsigned long
{
	return this->imageBaseAddress;
}

auto POEX::ImageSectionHeader::Name() const -> std::string
{
	auto nameArr = bFile->SubArray(this->offset, 8);
	return std::string(nameArr.begin(), nameArr.end());
}

auto POEX::ImageSectionHeader::Name(const std::string& name) -> void
{
	if (name.empty())
		THROW_OUT_OF_RANGE("[ERROR] 'name' cannot be empty.");
	auto nameArr = FixedNameLength(name);
	this->bFile->WriteBytes(this->offset, nameArr);
}

auto POEX::ImageSectionHeader::VirtualSize() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0008);
}

auto POEX::ImageSectionHeader::VirtualSize(const unsigned int& virtualSize) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0008, virtualSize);
}

auto POEX::ImageSectionHeader::VirtualAddress() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x000C);
}

auto POEX::ImageSectionHeader::VirtualAddress(const unsigned int& virtualAddress) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x000C, virtualAddress);
}

auto POEX::ImageSectionHeader::SizeOfRawData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0010);
}

auto POEX::ImageSectionHeader::SizeOfRawData(const unsigned int& sizeOfRawData) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0010, sizeOfRawData);
}

auto POEX::ImageSectionHeader::PointerToRawData() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0014);
}

auto POEX::ImageSectionHeader::PointerToRawData(const unsigned int& pointerToRawData) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0014, pointerToRawData);
}

auto POEX::ImageSectionHeader::PointerToRelocations() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x0018);
}

auto POEX::ImageSectionHeader::PointerToRelocations(const unsigned int& pointerToRelocations) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0018, pointerToRelocations);
}

auto POEX::ImageSectionHeader::PointerToLinenumbers() const -> unsigned int
{
	return this->bFile->ReadUnsignedInt(this->offset + 0x001C);
}

auto POEX::ImageSectionHeader::PointerToLinenumbers(const unsigned int& pointerToLinenumbers) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x001C, pointerToLinenumbers);
}

auto POEX::ImageSectionHeader::NumberOfRelocations() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0020);
}

auto POEX::ImageSectionHeader::NumberOfRelocations(const unsigned short& numberOfRelocations) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0020, numberOfRelocations);
}

auto POEX::ImageSectionHeader::NumberOfLinenumbers() const -> unsigned short
{
	return this->bFile->ReadUnsignedShort(this->offset + 0x0022);
}

auto POEX::ImageSectionHeader::NumberOfLinenumbers(const unsigned short& numberOfLinenumbers) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0022, numberOfLinenumbers);
}

auto POEX::ImageSectionHeader::Characteristics() const -> SectionFlag
{
	return SectionFlag(this->bFile->ReadUnsignedInt(this->offset + 0x0024));
}

auto POEX::ImageSectionHeader::Characteristics(const SectionFlag& characteristics) -> void
{
	this->bFile->WriteUnsignedInt(this->offset + 0x0024, (unsigned int)characteristics);
}

auto POEX::ImageSectionHeader::ToArray() -> std::vector<byte>
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

auto POEX::ImageSectionHeader::FixedNameLength(const std::string& name) -> std::vector<byte>
{
	auto nameArr = std::vector<byte>(name.begin(), name.end());
	if (nameArr.size() > 8)
		THROW_OUT_OF_RANGE("[ERROR] 'name' length is too long.");
	while (nameArr.size() < 8)
		nameArr.push_back((byte)0);

	return nameArr;
}
