#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include <vcruntime_exception.h>
#include <stdexcept>

#define THROW_EXCEPTION(_x_) throw std::exception(_x_)
#define THROW_OUT_OF_RANGE(_x_) throw std::out_of_range(_x_)
#define THROW_RUNTIME(_x_) throw std::runtime_error(_x_)

#define WRONG_LONG(_x_) (_x_ <= 0)
#define EMPTY_VECTOR(_x_) (_x_.empty())

#define SECTION_HEADER_SIZE 0x0028
#define ELFANEW 0x003C
#define PE_SIGNATURE_UNTIL_MAGIC 0x0018
#define IMPORT_TABLE_SIZE 0x0014

#define IMAGE_THUNK_DATA_86 0x0004
#define IMAGE_THUNK_DATA_64 0x0008

#define ORDINAL_BIT_86 0x80000000
#define ORDINAL_BIT_64 0x8000000000000000

#define ORDINAL_MASK_64 0x7FFFFFFFFFFFFFFF
#define ORDINAL_MASK_86 0x7FFFFFFF

/// <summary> 
/// File type architecture also Constants for the Optional header magic property.
/// </summary>
enum class FileType : unsigned short
{
	/// <summary>
	/// 32 bit file
	/// </summary>
	BIT32 = 0x10b,

	/// <summary>
	/// 64 bit file
	/// </summary>
	BIT64 = 0x20b,

	/// <summary>
	/// Rom file
	/// </summary>
	ROM = 0x107
};

/// <summary>
/// Machine type of image
/// </summary>
enum class MachineType : unsigned short
{
	/// <summary>
	/// Unknown
	/// </summary>
	UNKNOWN = 0x00,

	/// <summary>
	/// Intel 386
	/// </summary>
	I386 = 0x014c,

	/// <summary>
	/// Intel i860
	/// </summary>
	I860 = 0x014d,

	/// <summary>
	/// MIPS R3000
	/// </summary>
	R3000 = 0x0162,

	/// <summary>
	/// MIPS little endian (R4000)
	/// </summary>
	R4000 = 0x0166,

	/// <summary>
	/// MIPS R10000
	/// </summary>
	R10000 = 0x168,

	/// <summary>
	/// MIPS little endian WCI v2
	/// </summary>
	Wcemipsv2 = 0x169,

	/// <summary>
	/// old Alpha AXP
	/// </summary>
	OldAlpha = 0x183,

	/// <summary>
	/// Alpha AXP
	/// </summary>
	Alpha = 0x184,

    /// <summary>
    /// Hitachi SH3
    /// </summary>
    Sh3 = 0x1a2,

    /// <summary>
    /// Hitachi SH3 DSP
    /// </summary>
    Sh3Dsp = 0x1a3,

    /// <summary>
    /// unknown
    /// </summary>
    Sh3E = 0x1a4,

    /// <summary>
    /// Hitachi SH4
    /// </summary>
    Sh4 = 0x1a6,

    /// <summary>
    /// Hitachi SH5
    /// </summary>
    Sh5 = 0x1a8,

    /// <summary>
    /// ARM little endian
    /// </summary>
    Arm = 0x1c0,

    /// <summary>
    /// Thumb
    /// </summary>
    Thumb = 0x1c2,

    /// <summary>
    /// Matsushita AM33
    /// </summary>
    Am33 = 0x1d3,

    /// <summary>
    /// PowerPC little endian
    /// </summary>
    PowerPc = 0x1f0,

    /// <summary>
    /// PowerPC with floating point support
    /// </summary>
    PowerPcFp = 0x1f1,

    /// <summary>
    /// Intel IA64
    /// </summary>
    Ia64 = 0x200,

    /// <summary>
    /// MIPS16
    /// </summary>
    Mips16 = 0x266,

    /// <summary>
    /// Motorola 68000 series
    /// </summary>
    M68K = 0x268,

    /// <summary>
    /// Alpha AXP 64-bit
    /// </summary>
    Alpha64 = 0x284,

    /// <summary>
    /// MIPS with FPU
    /// </summary>
    MipsFpu = 0x366,

    /// <summary>
    /// MIPS16 with FPU
    /// </summary>
    MipsFpu16 = 0x466,

    /// <summary>
    /// Alpha AXP 64-bit
    /// </summary>
    Axp64 = Alpha64,

    /// <summary>
    /// unknown
    /// </summary>
    TriCore = 0x520,

    /// <summary>
    /// unknown
    /// </summary>
    Cef = 0xcef,

    /// <summary>
    /// EFI Byte Code
    /// </summary>
    Ebc = 0xebc,

    /// <summary>
    /// AMD AMD64 (Used for Intel x64, too)
    /// </summary>
    Amd64 = 0x8664,

    /// <summary>
    /// Mitsubishi M32R little endian
    /// </summary>
    M32R = 0x9041,

    /// <summary>
    /// clr pure MSIL (.Net)
    /// </summary>
    Cee = 0xc0ee,

    /// <summary>
    /// ARM65 Little-Endian
    /// </summary>
    Arm64 = 0xAA64,

    /// <summary>
    /// ARM Thumb-2 Little-Endian
    /// </summary>
    ArmNt = 0x01C4,

    /// <summary>
    /// Interacts with the host and not a WOW64 guest
    /// </summary>
    TargetHost = 0x0001,

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    LinuxDotnet64 = Amd64 ^ 0x4644, //0xFD1D

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    OsXDotnet64 = Amd64 ^ 0x7B79, //0xC020

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    FreeBSDDotnet64 = Amd64 ^ 0xADC4, //0x2BA0

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    NetBSDDotnet64 = Amd64 ^ 0x1993, //0x9FF7

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    SunDotnet64 = Amd64 ^ 0x1992, //0x9FF6

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    LinuxDotnet32 = I386 ^ 0x4644, //0x4708

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    OsXDotnet32 = I386 ^ 0x7B79, //0x7A35

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    FreeBSDDotnet32 = I386 ^ 0xADC4, //0xAC88

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    NetBSDDotnet32 = I386 ^ 0x1993, //0x18DF

    /// <summary>
    /// Defined by .NET
    /// https://github.com/dotnet/runtime/blob/61c658183231100a5836e833c86446ff51a4654b/src/coreclr/src/inc/pedecoder.h#L90-L104
    /// </summary>
    SunDotnet32 = I386 ^ 0x1992, //0x18DE
};

/// <summary>
/// Type of file Characteristics
/// </summary>

enum class FileCharacteristicsType : unsigned short
{
    /// <summary>
    /// Relocation stripped.
    /// </summary>
    RelocsStripped = 0x01,

    /// <summary>
    /// Executable image.
    /// </summary>
    ExecutableImage = 0x02,

    /// <summary>
    /// Line numbers stripped.
    /// </summary>
    LineNumsStripped = 0x04,

    /// <summary>
    /// Local symbols stripped.
    /// </summary>
    LocalSymsStripped = 0x08,

    /// <summary>
    /// (OBSOLTETE) Aggressively trim the working set.
    /// </summary>
    AggresiveWsTrim = 0x10,

    /// <summary>
    /// Application can handle addresses larger than 2 GB.
    /// </summary>
    LargeAddressAware = 0x20,

    /// <summary>
    /// (OBSOLTETE) Bytes of word are reversed.
    /// </summary>
    BytesReversedLo = 0x80,

    /// <summary>
    /// Supports 32 Bit words.
    /// </summary>
    BitMachine32 = 0x100,

    /// <summary>
    /// Debug stripped and stored in a separate file.
    /// </summary>
    DebugStripped = 0x200,

    /// <summary>
    /// If the image is on a removable media, copy and run it from the swap file.
    /// </summary>
    RemovableRunFromSwap = 0x400,

    /// <summary>
    /// If the image is on the network, copy and run it from the swap file.
    /// </summary>
    NetRunFromSwap = 0x800,

    /// <summary>
    /// The image is a system file.
    /// </summary>
    System = 0x1000,

    /// <summary>
    /// Is a dynamic loaded library and executable but cannot be run on its own.
    /// </summary>
    Dll = 0x2000,

    /// <summary>
    /// Image should be run only on uniprocessor.
    /// </summary>
    UpSystemOnly = 0x4000,

    /// <summary>
    /// (OBSOLETE) Reserved.
    /// </summary>
    BytesReversedHi = 0x8000
};

/// <summary>
/// Subsystem of the image.
/// </summary>
enum class SubsystemType : unsigned short 
{
    Unknown = 0,
    Native = 1,
    WindowsGui = 2,
    WindowsCui = 3,
    Os2Cui = 5,
    PosixCui = 7,
    WindowsCeGui = 9,
    EfiApplication = 10,
    EfiBootServiceDriver = 11,
    EfiRuntimeDriver = 12,
    EfiRom = 13,
    Xbox = 14,
    WindowsBootApplication = 16
};

/// <summary>
/// Constants for the Optional header DllCharacteristics property.
/// </summary>
enum class DllCharacteristicsType : unsigned short
{
    HighEntropyVA = 0x20,
    /// <summary>
    ///     DLL can be relocated at load time.
    /// </summary>
    DynamicBase = 0x40,

    /// <summary>
    ///     Enforces integrity checks.
    /// </summary>
    ForceIntegrity = 0x80,

    /// <summary>
    ///     Image is compatible with Data Execution Prevention (DEP).
    /// </summary>
    NxCompat = 0x100,

    /// <summary>
    ///     Image is isolation aware but should not be isolated.
    /// </summary>
    NoIsolation = 0x200,

    /// <summary>
    ///     No Secure Exception Handling (SEH)
    /// </summary>
    NoSeh = 0x400,

    /// <summary>
    ///     Do not bind the image.
    /// </summary>
    NoBind = 0x800,

    /// <summary>
    /// Image must execute in an AppContainer.
    /// </summary>
    AppContainer = 0x1000,

    /// <summary>
    ///     Image is a WDM driver.
    /// </summary>
    WdmDriver = 0x2000,

    /// <summary>
    /// Image supports Control Flow Guard.
    /// </summary>
    GuardCF = 0x4000,

    /// <summary>
    ///     Terminal server aware.
    /// </summary>
    TerminalServerAware = 0x8000
};

/// <summary>
/// The data directory type
/// </summary>
enum class DataDirectoryType : unsigned short
{
    /// <summary>
    ///     Export directory.
    /// </summary>
    Export = 0x00,

    /// <summary>
    ///     Import directory.
    /// </summary>
    Import = 0x01,

    /// <summary>
    ///     Resource directory.
    /// </summary>
    Resource = 0x02,

    /// <summary>
    ///     Exception directory for x64.
    /// </summary>
    Exception = 0x03,

    /// <summary>
    ///     Security directory.
    /// </summary>
    Security = 0x04,

    /// <summary>
    ///     Relocation directory.
    /// </summary>
    BaseReloc = 0x05,

    /// <summary>
    ///     Debug directory.
    /// </summary>
    Debug = 0x06,

    /// <summary>
    ///     Copyright directory (useless).
    /// </summary>
    Copyright = 0x07,

    /// <summary>
    ///     Global Pointer directory. Only interesting for Itanium systems.
    /// </summary>
    Globalptr = 0x08,

    /// <summary>
    ///     Thread Local Storage directory.
    /// </summary>
    TLS = 0x09,

    /// <summary>
    ///     Load Config directory.
    /// </summary>
    LoadConfig = 0x0A,

    /// <summary>
    ///     Bound Import directory. Precomputed import addresses
    ///     to speed up module loading.
    /// </summary>
    BoundImport = 0x0B,

    /// <summary>
    ///     Import Address Table directory.
    /// </summary>
    IAT = 0x0C,

    /// <summary>
    ///     Delayed Import directory. Imports which are loaded
    ///     with a delay for performance reasons.
    /// </summary>
    DelayImport = 0x0D,

    /// <summary>
    ///     COM Descriptor directory. For the .Net Header
    /// </summary>
    ComDescriptor = 0x0E,

    /// <summary>
    ///     Reserved for future use.
    /// </summary>
    Reserved = 0x0F
};

/// <summary>
/// The SectionFlags enumeration lists all possible flags which can be set in the section characteristics.
/// </summary>
enum class SectionFlag : unsigned int
{
    /// <summary>
    /// Reserved.
    /// </summary>
    TypeNoPad = 0x00000008,

    /// <summary>
    /// Section contains code.
    /// </summary>
    CntCode = 0x00000020,

    /// <summary>
    /// Section contains initialized data.
    /// </summary>
    CntInitializedData = 0x00000040,

    /// <summary>
    /// Section contains uninitialized data.
    /// </summary>
    CntUninitializedData = 0x00000080,

    /// <summary>
    /// Reserved.
    /// </summary>
    LnkOther = 0x00000100,

    /// <summary>
    /// Section contains comments or some  other type of information.
    /// </summary>
    LnkInfo = 0x00000200,

    /// <summary>
    /// Section contents will not become part of image.
    /// </summary>
    LnkRemove = 0x00000800,

    /// <summary>
    /// Section contents comdat.
    /// </summary>
    LnkComdat = 0x00001000,

    /// <summary>
    /// Reset speculative exceptions handling bits in the TLB entries for this section.
    /// </summary>
    NoDeferSpecExc = 0x00004000,

    /// <summary>
    /// Section content can be accessed relative to GP.
    /// </summary>
    Gprel = 0x00008000,

    /// <summary>
    /// Unknown.
    /// </summary>
    MemPurgeable = 0x00020000,

    /// <summary>
    /// Unknown.
    /// </summary>
    Mem16Bit = 0x00020000,

    /// <summary>
    /// Unknown.
    /// </summary>
    MemLocked = 0x00040000,

    /// <summary>
    /// Unknown.
    /// </summary>
    MemPreload = 0x00080000,

    /// <summary>
    /// Section alignment.
    /// </summary>
    Align1Bytes = 0x00100000,

    /// <summary>
    /// Section alignment.
    /// </summary>
    Align2Bytes = 0x00200000,

    /// <summary>
    /// Section alignment.
    /// </summary>
    Align4Bytes = 0x00300000,

    /// <summary>
    /// Section alignment.
    /// </summary>
    Align8Bytes = 0x00400000,

    /// <summary>
    /// Default alignment if no others are specified.
    /// </summary>
    Align16Bytes = 0x00500000,

    /// <summary>
    /// Section alignment.
    /// </summary>
    Align32Bytes = 0x00600000,

    /// <summary>
    /// Section alignment.
    /// </summary>
    Align64Bytes = 0x00700000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align128Bytes = 0x00800000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align256Bytes = 0x00900000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align512Bytes = 0x00A00000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align1024Bytes = 0x00B00000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align2048Bytes = 0x00C00000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align4096Bytes = 0x00D00000,

    /// <summary>
    ///  Section alignment.
    /// </summary>
    Align8192Bytes = 0x00E00000,

    /// <summary>
    /// Alignment mask.
    /// </summary>
    AlignMask = 0x00F00000,

    /// <summary>
    /// Section contains extended relocations.
    /// </summary>
    LnkNrelocOvfl = 0x01000000,

    /// <summary>
    /// Section can be discarded.
    /// </summary>
    MemDiscardable = 0x02000000,

    /// <summary>
    /// Section is not cache-able.
    /// </summary>
    MemNotCached = 0x04000000,

    /// <summary>
    /// Section is not page-able.
    /// </summary>
    MemNotPaged = 0x08000000,

    /// <summary>
    /// Section is shareable.
    /// </summary>
    MemShared = 0x10000000,

    /// <summary>
    /// Section is executable.
    /// </summary>
    MemExecute = 0x20000000,

    /// <summary>
    /// Section is readable.
    /// </summary>
    MemRead = 0x40000000,

    /// <summary>
    /// Section is write-able.
    /// </summary>
    MemWrite = 0x80000000
};