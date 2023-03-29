#include "../Headers/ImageCertificateDirectory.h"


ImageCertificateDirectory::ImageCertificateDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset)
	: bFile(bFile), offset(offset)
{
}

auto ImageCertificateDirectory::DwLength() const -> unsigned int
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

auto ImageCertificateDirectory::DwLength(const unsigned int& length) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, length);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageCertificateDirectory::WRevision() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageCertificateDirectory::WRevision(const unsigned short& revision) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0004, revision);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageCertificateDirectory::WCertificateType() const -> WinCertificateType
{
	try
	{
		return static_cast<WinCertificateType>(this->bFile->ReadUnsignedShort(this->offset + 0x0006));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageCertificateDirectory::WCertificateType(const WinCertificateType& type) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0006, static_cast<unsigned short>(type));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageCertificateDirectory::BCertificate() const -> std::vector<byte>
{
	try
	{
		if (this->offset + 0x8 > bFile->Length() || this->offset + DwLength() > bFile->Length())
			throw std::out_of_range("BCertificate not in PE file range.");

		return this->bFile->SubArray(this->offset + 0x0008, DwLength() - 8);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
