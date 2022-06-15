#include "../Headers/ImageDosHeader.h"

POEX::ImageDosHeader::ImageDosHeader(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto POEX::ImageDosHeader::E_magic() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0000);
}

auto POEX::ImageDosHeader::E_magic(const unsigned short& magic) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0000, magic);
}

auto POEX::ImageDosHeader::E_cblp() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0002);
}

auto POEX::ImageDosHeader::E_cblp(const unsigned short& cblp) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0002, cblp);
}

auto POEX::ImageDosHeader::E_cp() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0004);
}

auto POEX::ImageDosHeader::E_cp(const unsigned short& cp) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0004, cp);
}

auto POEX::ImageDosHeader::E_crlc() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0006);
}

auto POEX::ImageDosHeader::E_crlc(const unsigned short& crlc) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0006, crlc);
}

auto POEX::ImageDosHeader::E_cparhdr() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0008);
}

auto POEX::ImageDosHeader::E_cparhdr(const unsigned short& cparhdr) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0008, cparhdr);
}

auto POEX::ImageDosHeader::E_minalloc() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x000A);
}

auto POEX::ImageDosHeader::E_minalloc(const unsigned short& minalloc) -> void
{
	bFile->WriteUnsignedShort(offset + 0x000A, minalloc);
}

auto POEX::ImageDosHeader::E_maxalloc() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x000C);
}

auto POEX::ImageDosHeader::E_maxalloc(const unsigned short& maxalloc) -> void
{
	bFile->WriteUnsignedShort(offset + 0x000C, maxalloc);
}

auto POEX::ImageDosHeader::E_ss() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x000E);
}

auto POEX::ImageDosHeader::E_ss(const unsigned short& ss) -> void
{
	bFile->WriteUnsignedShort(offset + 0x000E, ss);
}

auto POEX::ImageDosHeader::E_sp() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0010);
}

auto POEX::ImageDosHeader::E_sp(const unsigned short& sp) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0010, sp);
}

auto POEX::ImageDosHeader::E_csum() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0012);
}

auto POEX::ImageDosHeader::E_csum(const unsigned short& csum) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0012, csum);
}

auto POEX::ImageDosHeader::E_ip() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0014);
}

auto POEX::ImageDosHeader::E_ip(const unsigned short& ip) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0014, ip);
}

auto POEX::ImageDosHeader::E_cs() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0016);
}

auto POEX::ImageDosHeader::E_cs(const unsigned short& cs) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0016, cs);
}

auto POEX::ImageDosHeader::E_lfarlc() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0018);
}

auto POEX::ImageDosHeader::E_lfarlc(const unsigned short& lfarlc) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0018, lfarlc);
}

auto POEX::ImageDosHeader::E_ovno() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x001A);
}

auto POEX::ImageDosHeader::E_ovno(const unsigned short& evno) -> void
{
	bFile->WriteUnsignedShort(offset + 0x001A, evno);
}

auto POEX::ImageDosHeader::E_res() const -> std::vector<unsigned short>
{
	auto data = std::vector<unsigned short>{};
	data.push_back(bFile->ReadUnsignedShort(this->offset + 0x001C));
	data.push_back(bFile->ReadUnsignedShort(this->offset + 0x001E));
	data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0020));
	data.push_back(bFile->ReadUnsignedShort(this->offset + 0x0022));

	return data;
}

auto POEX::ImageDosHeader::E_res(const std::vector<unsigned short>& res) -> void
{
	bFile->WriteUnsignedShort(offset + 0x001C, res[0]);
	bFile->WriteUnsignedShort(offset + 0x001E, res[1]);
	bFile->WriteUnsignedShort(offset + 0x0020, res[2]);
	bFile->WriteUnsignedShort(offset + 0x0022, res[3]);
}

auto POEX::ImageDosHeader::E_oemid() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0024);
}

auto POEX::ImageDosHeader::E_oemid(const unsigned short& oemid) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0024, oemid);
}

auto POEX::ImageDosHeader::E_oeminfo() const -> unsigned short
{
	return bFile->ReadUnsignedShort(this->offset + 0x0026);
}

auto POEX::ImageDosHeader::E_oeminfo(const unsigned short& oeminfo) -> void
{
	bFile->WriteUnsignedShort(offset + 0x0026, oeminfo);
}

auto POEX::ImageDosHeader::E_res2() const -> std::vector<unsigned short>
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

auto POEX::ImageDosHeader::E_res2(const std::vector<unsigned short>& res) -> void
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

auto POEX::ImageDosHeader::E_lfanew() const -> unsigned int
{
	return bFile->ReadUnsignedInt(this->offset + 0x003C);
}

auto POEX::ImageDosHeader::E_lfanew(const unsigned int& elfanew) -> void
{
	bFile->WriteUnsignedInt(offset + 0x003C, elfanew);
}
