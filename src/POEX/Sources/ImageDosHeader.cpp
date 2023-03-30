#include "../Headers/ImageDosHeader.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageDosHeader::ImageDosHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageDosHeader::E_magic() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_magic(const unsigned short& magic) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0000, magic);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cblp() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0002);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cblp(const unsigned short& cblp) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0002, cblp);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cp() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cp(const unsigned short& cp) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0004, cp);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_crlc() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0006);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_crlc(const unsigned short& crlc) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0006, crlc);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cparhdr() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cparhdr(const unsigned short& cparhdr) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0008, cparhdr);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_minalloc() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x000A);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_minalloc(const unsigned short& minalloc) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x000A, minalloc);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_maxalloc() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x000C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_maxalloc(const unsigned short& maxalloc) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x000C, maxalloc);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_ss() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x000E);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_ss(const unsigned short& ss) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x000E, ss);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_sp() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0010);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_sp(const unsigned short& sp) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0010, sp);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_csum() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0012);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_csum(const unsigned short& csum) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0012, csum);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_ip() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0014);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_ip(const unsigned short& ip) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0014, ip);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cs() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0016);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_cs(const unsigned short& cs) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0016, cs);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_lfarlc() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0018);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_lfarlc(const unsigned short& lfarlc) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0018, lfarlc);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_ovno() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x001A);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_ovno(const unsigned short& evno) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x001A, evno);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_res() const -> std::vector<unsigned short>
{
	try
	{
		auto data = std::vector<unsigned short>{};
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x001C));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x001E));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0020));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0022));

		return data;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_res(const std::vector<unsigned short>& res) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x001C, res[0]);
		bFile->WriteUnsignedShort(offset + 0x001E, res[1]);
		bFile->WriteUnsignedShort(offset + 0x0020, res[2]);
		bFile->WriteUnsignedShort(offset + 0x0022, res[3]);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_oemid() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0024);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_oemid(const unsigned short& oemid) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0024, oemid);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_oeminfo() const -> unsigned short
{
	try
	{
		return bFile->ReadUnsignedShort(this->offset + 0x0026);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_oeminfo(const unsigned short& oeminfo) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0026, oeminfo);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_res2() const -> std::vector<unsigned short>
{
	try
	{
		auto data = std::vector<unsigned short>{};
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0028));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x002A));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x002C));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x002E));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0030));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0032));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0034));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0036));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0038));
		data.push_back(bFile->ReadUnsignedShort(this->offset + 0x003A));

		return data;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_res2(const std::vector<unsigned short>& res) -> void
{
	try
	{
		bFile->WriteUnsignedShort(offset + 0x0028, res[0]);
		bFile->WriteUnsignedShort(offset + 0x002A, res[1]);
		bFile->WriteUnsignedShort(offset + 0x002C, res[2]);
		bFile->WriteUnsignedShort(offset + 0x002E, res[3]);
		bFile->WriteUnsignedShort(offset + 0x0030, res[4]);
		bFile->WriteUnsignedShort(offset + 0x0032, res[5]);
		bFile->WriteUnsignedShort(offset + 0x0034, res[6]);
		bFile->WriteUnsignedShort(offset + 0x0036, res[7]);
		bFile->WriteUnsignedShort(offset + 0x0038, res[8]);
		bFile->WriteUnsignedShort(offset + 0x003A, res[9]);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_lfanew() const -> unsigned int
{
	try
	{
		return bFile->ReadUnsignedInt(this->offset + 0x003C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageDosHeader::E_lfanew(const unsigned int& elfanew) -> void
{
	try
	{
		bFile->WriteUnsignedInt(offset + 0x003C, elfanew);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
