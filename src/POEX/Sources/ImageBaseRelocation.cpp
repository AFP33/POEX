#include "../Headers/ImageBaseRelocation.h"

ImageBaseRelocation::ImageBaseRelocation(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, const unsigned int& relocationSize) : 
	bFile(bFile), offset(offset), relocationSize(relocationSize)
{
	if (SizeOfBlock() > relocationSize)
		throw std::out_of_range("SizeOfBlock cannot be bigger than size of the Relocation Directory.");
	if (SizeOfBlock() < 8)
		throw std::out_of_range("SizeOfBlock cannot be smaller than 8.");
}

auto ImageBaseRelocation::VirtualAddress() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBaseRelocation::VirtualAddress(const unsigned int& va) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset, va);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBaseRelocation::SizeOfBlock() const -> unsigned int
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

auto ImageBaseRelocation::SizeOfBlock(const unsigned int& len) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, len);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageBaseRelocation::TypeOffsets() -> std::vector<std::unique_ptr<TypeOffset>>
{
	try
	{
		std::vector<std::unique_ptr<TypeOffset>> typeOffsets;
		for (unsigned int i = 0; i < (SizeOfBlock() - 8) / 2; i++)
			typeOffsets.push_back(std::make_unique<TypeOffset>(this->bFile, this->offset + 8 + i * 2));
		return typeOffsets;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

TypeOffset::TypeOffset(const std::shared_ptr<BufferFile>& bFile, const long& offset) :
	bFile(bFile), offset(offset)
{
}

auto TypeOffset::Type() const -> std::string
{
	try
	{
		auto to = this->bFile->ReadUnsignedShort(offset);
		auto type = (byte)(to >> 0x000C);
		return ParseType(type);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto TypeOffset::Offset() const -> unsigned short
{
	try
	{
		auto to = this->bFile->ReadUnsignedShort(offset);
		return (unsigned short)(to & 0x0FFF);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto TypeOffset::ParseType(const byte& type) const -> std::string
{
	switch (type)
	{
	case IMAGE_REL_BASED_ABSOLUTE:
		return "ABSOLUTE";
	case IMAGE_REL_BASED_HIGH:
		return "HIGH";
	case IMAGE_REL_BASED_LOW:
		return "LOW";
	case IMAGE_REL_BASED_HIGHLOW:
		return "HIGHLOW";
	case IMAGE_REL_BASED_HIGHADJ:
		return "HIGHADJ";
	case IMAGE_REL_BASED_MACHINE_SPECIFIC_5:
		return "HIGHMACHINE SPECIFIC 5ADJ";
	case IMAGE_REL_BASED_RESERVED:
		return "RESERVED";
	case IMAGE_REL_BASED_MACHINE_SPECIFIC_7:
		return "MACHINE SPECIFIC 7";
	case IMAGE_REL_BASED_MACHINE_SPECIFIC_8:
		return "MACHINE SPECIFIC 8";
	case IMAGE_REL_BASED_MACHINE_SPECIFIC_9:
		return "MACHINE SPECIFIC 9";
	case IMAGE_REL_BASED_DIR64:
		return "DIR64";
	default:
		return "Unknown";
	}
}
