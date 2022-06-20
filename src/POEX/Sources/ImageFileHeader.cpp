#include "../Headers/ImageFileHeader.h"

ImageFileHeader::ImageFileHeader(const std::shared_ptr<BufferFile>& bFile, 
    const long& offset) : bFile(bFile), offset(offset)
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageFileHeader::ToString(MachineType machine) -> std::string
{
    switch (machine)
    {
        case MachineType::I386: return "Intel 386";
        case MachineType::I860: return "Intel i860";
        case MachineType::R3000: return "MIPS R3000";
        case MachineType::R4000: return "MIPS little endian (R4000)";
        case MachineType::R10000: return "MIPS R10000";
        case MachineType::Wcemipsv2: return "MIPS little endian WCI v2";
        case MachineType::OldAlpha: return "old Alpha AXP";
        case MachineType::Alpha: return "Alpha AXP";
        case MachineType::Sh3: return "Hitachi SH3";
        case MachineType::Sh3Dsp: return "Hitachi SH3 DSP";
        case MachineType::Sh3E: return "Hitachi SH3E";
        case MachineType::Sh4: return "Hitachi SH4";
        case MachineType::Sh5: return "Hitachi SH5";
        case MachineType::Arm: return "ARM little endian";
        case MachineType::Thumb: return "Thumb";
        case MachineType::Am33: return "Matsushita AM33";
        case MachineType::PowerPc: return "PowerPC little endian";
        case MachineType::PowerPcFp: return "PowerPC with floating point support";
        case MachineType::Ia64: return "Intel IA64";
        case MachineType::Mips16: return "MIPS16";
        case MachineType::M68K: return "Motorola 68000 series";
        case MachineType::Alpha64: return "Alpha AXP 64-bit";
        case MachineType::MipsFpu: return "MIPS with FPU";
        case MachineType::TriCore: return "Tricore";
        case MachineType::Cef: return "CEF";
        case MachineType::MipsFpu16: return "MIPS16 with FPU";
        case MachineType::Ebc: return "EFI Byte Code";
        case MachineType::Amd64: return "AMD64";
        case MachineType::M32R: return "Mitsubishi M32R little endian";
        case MachineType::Cee: return "clr pure MSIL";
        case MachineType::Arm64: return "ARM64 Little-Endian";
        case MachineType::ArmNt: return "ARM Thumb-2 Little-Endian";
        case MachineType::TargetHost: return "Interacts with the host and not a WOW64 guest";
        case MachineType::LinuxDotnet64: return "Linux .NET x64";
        case MachineType::LinuxDotnet32: return "Linux .NET x86";
        case MachineType::OsXDotnet64: return "Mac OS .NET x64";
        case MachineType::OsXDotnet32: return "Mac OS .NET x86";
        case MachineType::FreeBSDDotnet64: return "FreeBSD .NET x64";
        case MachineType::FreeBSDDotnet32: return "FreeBSD .NET x86";
        case MachineType::NetBSDDotnet64: return "NetBSD .NET x64";
        case MachineType::NetBSDDotnet32: return "NetBSD .NET x86";
        case MachineType::SunDotnet64: return "Sun .NET x64";
        case MachineType::SunDotnet32: return "Sun .NET x86";
        default:
        return "NOT FOUND MACHINE TYPE";
    }
}

auto ImageFileHeader::ToString(FileCharacteristicsType fileCharacteristicsType) -> std::string
{
    switch (fileCharacteristicsType)
    {
        case FileCharacteristicsType::RelocsStripped: return "RelocsStripped";
        case FileCharacteristicsType::ExecutableImage: return "ExecutableImage";
        case FileCharacteristicsType::LineNumsStripped: return "LineNumsStripped";
        case FileCharacteristicsType::LocalSymsStripped: return "LocalSymsStripped";
        case FileCharacteristicsType::AggresiveWsTrim: return "AggresiveWsTrim";
        case FileCharacteristicsType::LargeAddressAware: return "LargeAddressAware";
        case FileCharacteristicsType::BytesReversedLo: return "BytesReversedLo";
        case FileCharacteristicsType::BitMachine32: return "BitMachine32";
        case FileCharacteristicsType::DebugStripped: return "DebugStripped";
        case FileCharacteristicsType::RemovableRunFromSwap: return "RemovableRunFromSwap";
        case FileCharacteristicsType::NetRunFromSwap: return "NetRunFromSwap";
        case FileCharacteristicsType::System: return "System";
        case FileCharacteristicsType::Dll: return "DLL";
        case FileCharacteristicsType::UpSystemOnly: return "UpSystemOnly";
        case FileCharacteristicsType::BytesReversedHi: return "BytesReversedHi";
        default: return "NOT FOUND File Characteristics Type";
    }
}

auto ImageFileHeader::Machine() const -> MachineType
{
	return static_cast<MachineType>(this->bFile->ReadUnsignedShort(this->offset + 0x0000));
}

auto ImageFileHeader::Machine(MachineType machine) -> void
{
	this->bFile->WriteUnsignedShort(this->offset + 0x0000, (unsigned short)machine);
}

auto ImageFileHeader::NumberOfSection() const -> unsigned short
{
    return this->bFile->ReadUnsignedShort(this->offset + 0x0002);
}

auto ImageFileHeader::NumberOfSection(const unsigned short& numberOfSection) -> void
{
    this->bFile->WriteUnsignedShort(this->offset + 0x0002, numberOfSection);
}

auto ImageFileHeader::TimeDateStamp() const -> unsigned int
{
    return this->bFile->ReadUnsignedInt(this->offset + 0x0004);
}

auto ImageFileHeader::TimeDateStamp(const unsigned int& timeDateStamp) -> void
{
    this->bFile->WriteUnsignedInt(this->offset + 0x0004, timeDateStamp);
}

auto ImageFileHeader::PointerToSymbolTable() const -> unsigned int
{
    return this->bFile->ReadUnsignedShort(this->offset + 0x0008);
}

auto ImageFileHeader::PointerToSymbolTable(const unsigned int& pointerToSymbolTable) -> void
{
    this->bFile->WriteUnsignedInt(this->offset + 0x0008, pointerToSymbolTable);
}

auto ImageFileHeader::NumberOfSymbols() const -> unsigned int
{
    return this->bFile->ReadUnsignedInt(this->offset + 0x000C);
}

auto ImageFileHeader::NumberOfSymbols(const unsigned int& numberOfSymbols) -> void
{
    this->bFile->WriteUnsignedInt(this->offset + 0x000C, numberOfSymbols);
}

auto ImageFileHeader::SizeOfOptionalHeader() const -> unsigned short
{
    return this->bFile->ReadUnsignedShort(this->offset + 0x0010);
}

auto ImageFileHeader::SizeOfOptionalHeader(const unsigned short& sizeOfOptionalHeader) -> void
{
    this->bFile->WriteUnsignedShort(this->offset + 0x0010, sizeOfOptionalHeader);
}

auto ImageFileHeader::Characteristics() const -> FileCharacteristicsType
{
    return static_cast<FileCharacteristicsType>(this->bFile->ReadUnsignedShort(this->offset + 0x0012));
}

auto ImageFileHeader::Characteristics(FileCharacteristicsType fileCharacteristicsType) -> void
{
    this->bFile->WriteUnsignedShort(this->offset + 0x0012, (unsigned short)fileCharacteristicsType);
}
