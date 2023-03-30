#include "../Headers/ImageDebugDirectory.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageDebugDirectory::ImageDebugDirectory(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageDebugDirectory::Characteristics() const -> unsigned int
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

auto ImageDebugDirectory::Characteristics(const unsigned int& characteristics) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, characteristics);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::TimeDateStamp() const -> unsigned int
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

auto ImageDebugDirectory::TimeDateStamp(const unsigned int& time) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0004, time);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::MajorVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::MajorVersion(const unsigned short& majorVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0008, majorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::MinorVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x000A);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::MinorVersion(const unsigned short& minorVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0008, minorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::Type() const -> unsigned int
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

auto ImageDebugDirectory::Type(const unsigned int& type) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x000C, type);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::DebugType() const -> DebugDirectoryType
{
	try
	{
		return static_cast<DebugDirectoryType>(this->Type());
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::DebugType(const DebugDirectoryType& type) -> void
{
	try
	{
		this->Type((unsigned int)type);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::SizeOfData() const -> unsigned int
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

auto ImageDebugDirectory::SizeOfData(const unsigned int& length) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0010, length);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::AddressOfRawData() const -> unsigned int
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

auto ImageDebugDirectory::AddressOfRawData(const unsigned int& offset) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0014, offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::PointerToRawData() const -> unsigned int
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

auto ImageDebugDirectory::PointerToRawData(const unsigned int& offset) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0018, offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::PdbInfo() const -> std::unique_ptr<CvInfoPdb70>
{
	try
	{
		if (DebugType() != DebugDirectoryType::CodeView)
			return NULL;

		return std::make_unique<CvInfoPdb70>(this->bFile, PointerToRawData());
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDebugDirectory::ExtendedDllCharacteristics() const -> ExtendedDllCharacteristicsType
{
	try
	{
		if (DebugType() != DebugDirectoryType::ExtendedDllCharacteristics)
			return ExtendedDllCharacteristicsType::NullType;

		return static_cast<ExtendedDllCharacteristicsType>(
			this->bFile->ReadUnsignedInt(this->PointerToRawData()));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

CvInfoPdb70::CvInfoPdb70(const std::shared_ptr<BufferFile>& bFile, const long& offset) :
	bFile(bFile), offset(offset)
{
}

auto CvInfoPdb70::CvSignature() const -> unsigned int
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

auto CvInfoPdb70::CvSignature(const unsigned int& cvSignature) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x0000, cvSignature);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto CvInfoPdb70::Signature() const -> GUID
{
	try
	{
		std::vector<byte> readed;
		for (size_t i = 0; i < 16; i++)
			readed.push_back(this->bFile->ReadByte(offset + 0x0004 + i));
		return *reinterpret_cast<GUID*>(&readed[0]);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto CvInfoPdb70::Signature(const GUID& signature) -> void
{
	try
	{
		std::vector<byte> as;
		as.push_back(signature.Data1);
		as.push_back(signature.Data2);
		as.push_back(signature.Data3);
		as.push_back((byte)signature.Data4);
		//this->bFile->WriteBytes(offset + 0x0004, as);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto CvInfoPdb70::Age() const -> unsigned int
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

auto CvInfoPdb70::Age(const unsigned int& age) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x0014, age);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto CvInfoPdb70::PdbFileName() const -> std::string
{
	try
	{
		return this->bFile->ReadAsciiString(offset + 0x0018);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
