#include "../Headers/ImageTlsDirectory.h"
#include "../Headers/Utils.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageTlsDirectory::ImageTlsDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders, const bool& is64Bit) :
	bFile(bFile), offset(offset), imageSectionHeaders(imageSectionHeaders), is64Bit(is64Bit)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageTlsDirectory::Callbacks() -> std::vector<ImageTlsCallback>
{
	try
	{
		std::vector<ImageTlsCallback> callbacks;
		auto addressOfCallbacks = AddressOfCallBacks();
		auto rawAddressOfCallbacks = Utils::VaToOffset(addressOfCallbacks, this->imageSectionHeaders);

		unsigned int iterator = 0;
		while (true)
		{
			if (is64Bit)
			{
				auto obj = ImageTlsCallback(this->bFile, rawAddressOfCallbacks + iterator * 8, 
					is64Bit);
				if (obj.Callback() == 0)
					break;

				callbacks.push_back(obj);
				iterator++;
			}
			else
			{
				auto obj = ImageTlsCallback(this->bFile, rawAddressOfCallbacks + iterator * 4,
					is64Bit);
				if (obj.Callback() == 0)
					break;

				callbacks.push_back(obj);
				iterator++;
			}
		}
		return callbacks;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::StartAddressOfRawData() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(this->offset + 0x0000) :
			this->bFile->ReadUnsignedInt(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::StartAddressOfRawData(const unsigned long& off) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(this->offset + 0x0000, off);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x0000, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::EndAddressOfRawData() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(this->offset + 8) :
			this->bFile->ReadUnsignedInt(this->offset + 4);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::EndAddressOfRawData(const unsigned long& off) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(this->offset + 0x0008, off);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x0004, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::AddressOfIndex() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(this->offset + 0x0010) :
			this->bFile->ReadUnsignedInt(this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::AddressOfIndex(const unsigned long& off) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(this->offset + 0x0010, off);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x0008, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::AddressOfCallBacks() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(this->offset + 0x0018) :
			this->bFile->ReadUnsignedInt(this->offset + 0x000C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::AddressOfCallBacks(const unsigned long& off) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(this->offset + 0x0018, off);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x000C, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::SizeOfZeroFill() const -> unsigned int
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedInt(this->offset + 0x0020) :
			this->bFile->ReadUnsignedInt(this->offset + 0x0010);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::SizeOfZeroFill(const unsigned int& length) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedInt(this->offset + 0x0020, length);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x0010, length);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::Characteristics() const -> unsigned int
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedInt(this->offset + 0x0024) :
			this->bFile->ReadUnsignedInt(this->offset + 0x0014);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsDirectory::Characteristics(const unsigned int& characteristics) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedInt(this->offset + 0x0024, characteristics);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x0014, characteristics);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

ImageTlsCallback::ImageTlsCallback(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const bool& is64Bit) :
	bFile(bFile), offset(offset), is64Bit(is64Bit)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageTlsCallback::Callback() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(this->offset + 0x0000) :
			this->bFile->ReadUnsignedInt(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageTlsCallback::Callback(const unsigned long& off) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(this->offset + 0x0000, off);
		else
			this->bFile->WriteUnsignedInt(this->offset + 0x0000, (unsigned int)off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
