#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"

/// <summary>
/// An image has potentially multiple entries of ImageDebugDirectory.
/// This is the "Type" of an entry.
/// Main source is winnt.h
/// See https://docs.microsoft.com/en-us/windows/win32/debug/pe-format#debug-type
/// and https://docs.microsoft.com/en-us/dotnet/api/system.reflection.portableexecutable.debugdirectoryentrytype?view=net-5.0
/// </summary>
enum DebugDirectoryType : unsigned int
{
    /// <summary>
    ///     An unknown value that should be ignored by all tools.
    /// </summary>
    Null = 0,

    /// <summary>
    ///     The COFF debug information (line numbers, symbol table, and string table). 
    ///     This type of debug information is also pointed to by fields in the file headers.
    /// </summary>
    Coff = 1,

    /// <summary>
    ///     Associated PDB file description. For more information, see the specification:
    ///     https://github.com/dotnet/runtime/blob/master/docs/design/specs/PE-COFF.md#codeview-debug-directory-entry-type-2
    /// </summary>
    CodeView = 2,

    /// <summary>
    ///     The frame pointer omission (FPO) information. 
    ///     This information tells the debugger how to interpret nonstandard stack frames, 
    ///     which use the EBP register for a purpose other than as a frame pointer.
    ///     Check winnt.h for struct FPO_DATA
    /// </summary>
    FramePointerOmission = 3,

    /// <summary>
    ///     The location of DBG file.
    /// </summary>
    Misc = 4,

    /// <summary>
    ///     A copy of .pdata section.
    /// </summary>
    Exception = 5,

    /// <summary>
    ///     Reserved.
    /// </summary>
    Fixup = 6,

    /// <summary>
    ///     The mapping from an RVA in image to an RVA in source image.
    /// </summary>
    OMapToSource = 7,

    /// <summary>
    ///     The mapping from an RVA in source image to an RVA in image.
    /// </summary>
    OMapFromSource = 8,

    /// <summary>
    ///     Reserved for Borland.
    /// </summary>
    Borland = 9,

    /// <summary>
    ///     Reserved.
    /// </summary>
    Reserved10 = 10,

    /// <summary>
    ///     Reserved.
    /// </summary>
    Clsid = 11,

    /// <summary>
    ///     5 uint values which "dumpbin /headers abc.exe" dumps as e.g.:
    ///     Counts: Pre-VC++ 11.00=0, C/C++=28, /GS=28, /sdl=1, guardN=27
    /// </summary>
    VcFeature = 12,

    /// <summary>
    ///     Profile guided optimization (aka PGO)
    /// </summary>
    Pogo = 13,

    /// <summary>
    ///     
    /// </summary>
    Iltcg = 14,

    /// <summary>
    ///     
    /// </summary>
    Mpx = 15,

    /// <summary>
    ///     The presence of this entry indicates a deterministic PE/COFF file.
    ///     The tool that produced the deterministic PE/COFF file guarantees that 
    ///     the entire content of the file is based solely on documented inputs given 
    ///     to the tool (such as source files, resource files, and compiler options) 
    ///     rather than ambient environment variables (such as the current time, 
    ///     the operating system, and the bitness of the process running the tool). 
    ///     The value of field TimeDateStamp in COFF File Header of a deterministic 
    ///     PE/COFF file does not indicate the date and time when the file was produced 
    ///     and should not be interpreted that way. Instead, the value of the field is 
    ///     derived from a hash of the file content. 
    ///     The algorithm to calculate this value is an implementation detail of the tool 
    ///     that produced the file. The debug directory entry of type Reproducible must 
    ///     have all fields, except for Type zeroed.
    ///     For more information, see the specification:
    ///     https://github.com/dotnet/runtime/blob/master/docs/design/specs/PE-COFF.md#deterministic-debug-directory-entry-type-16
    /// </summary>
    Reproducible = 16,

    /// <summary>
    ///     The entry points to a blob containing Embedded Portable PDB. The Embedded Portable PDB blob has the following format:
    ///     - blob ::= uncompressed-size data
    ///     - Data spans the remainder of the blob and contains a Deflate-compressed Portable PDB.
    ///     For more information, see the specification:
    ///     https://github.com/dotnet/runtime/blob/master/docs/design/specs/PE-COFF.md#embedded-portable-pdb-debug-directory-entry-type-17
    /// </summary>
    EmbeddedPortablePdb = 17,

    /// <summary>
    ///     
    /// </summary>
    Reserved18 = 18,

    /// <summary>
    ///     The entry stores a crypto hash of the content of the symbol file the PE/COFF 
    ///     file was built with. The hash can be used to validate that a given PDB file 
    ///     was built with the PE/COFF file and not altered in any way. 
    ///     More than one entry can be present if multiple PDBs were produced during the 
    ///     build of the PE/COFF file (for example, private and public symbols). 
    ///     For more information, see the specification:
    ///     https://github.com/dotnet/runtime/blob/master/docs/design/specs/PE-COFF.md#pdb-checksum-debug-directory-entry-type-19
    /// </summary>
    PdbChecksum = 19,

    /// <summary>
    ///     Extended DLL characteristics bits.
    ///     Raw data points to 4 bytes of type ExtendedDllCharacteristicsType
    /// </summary>
    ExtendedDllCharacteristics = 20
};

/// <summary>
/// Possible bit-field values when ImageDebugDirectory.Type is DebugDirectoryType.ExtendedDllCharacteristics
/// </summary>
enum ExtendedDllCharacteristicsType : unsigned int
{
    /// <summary>
    ///     
    /// </summary>
    NullType = 0x00,

    /// <summary>
    ///     Image was linked with /CETCOMPAT thus declares it is CET/Shadow-Stack/HSP compatible.
    /// </summary>
    CetCompat = 0x01,

    /// <summary>
    ///     
    /// </summary>
    CetCompatStrictMode = 0x02,

    /// <summary>
    ///     
    /// </summary>
    CetSetContextIpValidationRelaxMod = 0x04,

    /// <summary>
    ///     
    /// </summary>
    CetDynamicApisAllowInProc = 0x08,

    /// <summary>
    ///     
    /// </summary>
    CetReserved1 = 0x10,

    /// <summary>
    ///     
    /// </summary>
    CetReserved2 = 0x20
};

/// <summary>
/// Codeview PDB information from the Debug directory.
/// </summary>
struct CvInfoPdb70
{
    CvInfoPdb70(const std::shared_ptr<BufferFile>& bFile, const long& offset);
    ~CvInfoPdb70() = default;

    /// <summary>
    /// Codeview signature.
    /// Typically 0x53445352 = 'RSDS'
    /// </summary>
    /// <returns></returns>
    auto CvSignature() const -> unsigned int;

    /// <summary>
    /// Codeview signature.
    /// Typically 0x53445352 = 'RSDS'
    /// </summary>
    /// <param name="cvSignature">Codeview signature</param>
    /// <returns></returns>
    auto CvSignature(const unsigned int& cvSignature) -> void;

    /// <summary>
    /// The PDB signature is a GUID to identify the PDB file which belongs to the PE file.
    /// </summary>
    /// <returns>guid</returns>
    auto Signature() const->GUID;

    /// <summary>
    /// The PDB signature is a GUID to identify the PDB file which belongs to the PE file.
    /// </summary>
    /// <param name="signature">guid</param>
    /// <returns></returns>
    auto Signature(const GUID& signature) -> void;

    /// <summary>
    /// PDB Age is the iteration of the PDB. The first iteration is 1. 
    /// The iteration is incremented each time the PDB content is augmented.
    /// </summary>
    /// <returns>Iteration if PDB</returns>
    auto Age() const -> unsigned int;

    /// <summary>
    /// PDB Age is the iteration of the PDB. The first iteration is 1. 
    /// The iteration is incremented each time the PDB content is augmented.
    /// </summary>
    /// <param name="age">Iteration if PDB</param>
    /// <returns></returns>
    auto Age(const unsigned int& age) -> void;

    /// <summary>
    /// Original file name of the PDB that belongs to the PE file.
    /// </summary>
    /// <returns></returns>
    auto PdbFileName() const->std::string;

private:
    CvInfoPdb70()=default;
    CvInfoPdb70(const CvInfoPdb70&) = default;

    std::shared_ptr<BufferFile> bFile;
    long offset;
};

/// <summary>
/// The ImageDebugDirectory hold debug information about the PE file.
/// </summary>
class ImageDebugDirectory
{
public: 

	/// <summary>
	/// Create a new ImageDebugDirectory object.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset to the debug structure in the PE file.</param>
	ImageDebugDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset);
	~ImageDebugDirectory() = default;

	/// <summary>
	/// Characteristics of the debug information.
	/// </summary>
	/// <returns>Characteristics</returns>
	auto Characteristics() const->unsigned int;

	/// <summary>
	/// Characteristics of the debug information.
	/// </summary>
	/// <param name="characteristics">Characteristics</param>
	/// <returns></returns>
	auto Characteristics(const unsigned int& characteristics) -> void;

	/// <summary>
	/// Time and date stamp
	/// </summary>
	/// <returns>Time and date stamp</returns>
	auto TimeDateStamp() const->unsigned int;

	/// <summary>
	/// Time and date stamp
	/// </summary>
	/// <param name="time">Time and date stamp</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& time) -> void;

	/// <summary>
	/// Major Version.
	/// </summary>
	/// <returns>Major Version.</returns>
	auto MajorVersion() const->unsigned short;

	/// <summary>
	/// Major Version.
	/// </summary>
	/// <param name="majorVersion"></param>
	/// <returns></returns>
	auto MajorVersion(const unsigned short& majorVersion) -> void;

	/// <summary>
	/// Minor Version.
	/// </summary>
	/// <returns></returns>
	auto MinorVersion() const->unsigned short;
    
	/// <summary>
	/// Minor Version.
	/// </summary>
	/// <param name="minorVersion">Minor Version.</param>
	/// <returns></returns>
	auto MinorVersion(const unsigned short& minorVersion) -> void;

	/// <summary>
    /// Type
    /// 1: Coff
    /// 2: CV-PDB
    /// 9: Borland
	/// </summary>
	/// <returns></returns>
	auto Type() const->unsigned int;

	/// <summary>
    /// Type
    /// 1: Coff
    /// 2: CV-PDB
    /// 9: Borland
	/// </summary>
	/// <param name="type">type</param>
	/// <returns></returns>
	auto Type(const unsigned int& type) -> void;

	/// <summary>
	/// Type of Entry
	/// </summary>
	/// <returns>Type</returns>
	auto DebugType() const->DebugDirectoryType;

	/// <summary>
	/// Type of Entry
	/// </summary>
	/// <param name="type">type</param>
	/// <returns></returns>
	auto DebugType(const DebugDirectoryType& type) -> void;

	/// <summary>
	/// Size of data.
	/// </summary>
	/// <returns>Size</returns>
	auto SizeOfData() const->unsigned int;

	/// <summary>
	/// Size of data.
	/// </summary>
	/// <param name="length">Size</param>
	/// <returns></returns>
	auto SizeOfData(const unsigned int& length) -> void;

	/// <summary>
	/// Address of raw data.
	/// </summary>
	/// <returns>offset</returns>
	auto AddressOfRawData() const->unsigned int;

	/// <summary>
	/// Address of raw data.
	/// </summary>
	/// <param name="offset">pffset</param>
	/// <returns></returns>
	auto AddressOfRawData(const unsigned int& offset) -> void;

	/// <summary>
	/// Pointer to raw data.
	/// </summary>
	/// <returns>Pointer</returns>
	auto PointerToRawData() const->unsigned int;

	/// <summary>
	/// Pointer to raw data.
	/// </summary>
	/// <param name="offset">Pointer</param>
	/// <returns></returns>
	auto PointerToRawData(const unsigned int& offset) -> void;

	/// <summary>
	/// PDB information if the "Type" is IMAGE_DEBUG_TYPE_CODEVIEW.
	/// </summary>
	/// <returns></returns>
	auto PdbInfo() const->std::unique_ptr<CvInfoPdb70>;

	/// <summary>
	/// Flags if the "Type" is IMAGE_DEBUG_TYPE_EX_DLLCHARACTERISTICS
	/// </summary>
	/// <returns>characteristics</returns>
	auto ExtendedDllCharacteristics() const->ExtendedDllCharacteristicsType;

private:
	ImageDebugDirectory() = default;
	ImageDebugDirectory(const ImageDebugDirectory&) = default;

    std::shared_ptr<BufferFile> bFile;
    long offset;
};