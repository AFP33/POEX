#pragma once

#include "BufferFile.h"
#include "ImageSectionHeader.h"
#include "ImageDataDirectory.h"

class ImageResourceDirectory;
struct ImageResourceDirectoryEntry;

/// <summary>
///     Mapping from Resources Group ID to a meaningful
///     string. Used for ID resources (opposite to named resource).
/// </summary>
enum ResourceGroupIdType : unsigned int
{
	/// <summary>
	///     Cursor resource.
	/// </summary>
	Cursor = 1,

	/// <summary>
	///     Bitmap resource.
	/// </summary>
	Bitmap = 2,

	/// <summary>
	///     Icon resource.
	/// </summary>
	Icon = 3,

	/// <summary>
	///     Menu resource.
	/// </summary>
	Menu = 4,

	/// <summary>
	///     Dialog resource.
	/// </summary>
	Dialog = 5,

	/// <summary>
	///     String resource.
	/// </summary>
	String = 6,

	/// <summary>
	///     Font Directory resource.
	/// </summary>
	FontDirectory = 7,

	/// <summary>
	///     Fonst resource.
	/// </summary>
	Font = 8,

	/// <summary>
	///     Accelerator resource.
	/// </summary>
	Accelerator = 9,

	/// <summary>
	///     RC Data resource.
	/// </summary>
	RcData = 10,

	/// <summary>
	///     Message Table resource.
	/// </summary>
	MessageTable = 11,

	/// <summary>
	/// Hardware-independent cursor resource. (RT_CURSOR) + 11)
	/// </summary>
	GroupCursor = 12,

	/// <summary>
	///     Group Icon resource.
	/// </summary>
	GroupIcon = 14,

	/// <summary>
	///     Version resource.
	/// </summary>
	Version = 16,

	/// <summary>
	///     Dlg Include resource.
	/// </summary>
	DlgInclude = 17,

	/// <summary>
	///     Plug and Play resource.
	/// </summary>
	PlugAndPlay = 19,

	/// <summary>
	///     VXD resource.
	/// </summary>
	VXD = 20,

	/// <summary>
	///     Animated Cursor resource.
	/// </summary>
	AnimatedCurser = 21,

	/// <summary>
	///     Animated Icon resource.
	/// </summary>
	AnimatedIcon = 22,

	/// <summary>
	///     HTML resource.
	/// </summary>
	HTML = 23,

	/// <summary>
	///     Manifest resource.
	/// </summary>
	Manifest = 24
};

/// <summary>
/// Represents a Unicode string used for resource names in the resource section.
/// </summary>
struct ImageResourceDirStringU
{
	/// <summary>
	/// Create a new ImageResourceDirStringU Unicode string.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Raw offset of the string.</param>
	ImageResourceDirStringU(const std::shared_ptr<BufferFile>& bFile, const long& offset);

	/// <summary>
	/// Length of the string in Unicode characters, *not* in bytes.
	/// 1 Unicode char = 2 bytes.
	/// </summary>
	/// <returns></returns>
	auto Length() const -> unsigned short;

	/// <summary>
	/// Length of the string in Unicode characters, *not* in bytes.
	/// 1 Unicode char = 2 bytes.
	/// </summary>
	/// <param name="len">length</param>
	/// <returns></returns>
	auto Length(const unsigned short& len) -> void;

	/// <summary>
	/// The Unicode string as a .Net string.
	/// </summary>
	/// <returns></returns>
	auto NameString() const->std::wstring;

private:
	ImageResourceDirStringU() = default;
	ImageResourceDirStringU(const ImageResourceDirStringU&) = default;


	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;

	friend class PE;
};

/// <summary>
/// The resource directory entry represents one entry (e.g. icon) in a resource directory.
/// </summary>
struct ImageResourceDirectoryEntry
{
	ImageResourceDirectoryEntry(const std::shared_ptr<BufferFile>& bFile, 
		const std::shared_ptr<ImageResourceDirectory>& parent,
		const long& offset, const long& resourceDirectoryOffset);

	/// <summary>
	/// Get the Resource Directory which the Directory Entry points
	/// to if the Directory Entry has DataIsDirectory set.
	/// </summary>
	/// <returns>Pointer to ImageResourceDirectory</returns>
	auto ResourceDirectory() -> std::shared_ptr<ImageResourceDirectory>;

	/// <summary>
	/// Set the Resource Directory which the Directory Entry points
	/// to if the Directory Entry has DataIsDirectory set.
	/// </summary>
	/// <param name="resourceDir">Pointer of ImageResourceDirectory</param>
	/// <returns></returns>
	auto ResourceDirectory(const std::shared_ptr<ImageResourceDirectory>& resourceDir) -> void;

	/// <summary>
	/// ImageResourceDirectoryEntry in which this entry resides.
	/// </summary>
	/// <returns></returns>
	auto Parent() const->std::shared_ptr<ImageResourceDirectory>;

	/// <summary>
	/// The resolved name as a string if it's a named resource or a known resource ID.
	/// </summary>
	/// <returns></returns>
	auto NameResolve() const->std::string;

	/// <summary>
	/// Address of the name if its a named resource.
	/// </summary>
	/// <returns>Address of the name</returns>
	auto Name() const->unsigned int;

	/// <summary>
	/// Address of the name if its a named resource.
	/// </summary>
	/// <param name="name">Address of the name</param>
	/// <returns></returns>
	auto Name(const unsigned int& name) -> void;

	/// <summary>
	/// The ID if its a ID resource.
	/// </summary>
	/// <returns>id</returns>
	auto ID() const->unsigned int;

	/// <summary>
	/// The ID if its a ID resource.
	/// </summary>
	/// <param name="id">id</param>
	/// <returns></returns>
	auto ID(const unsigned int& id) -> void;

	/// <summary>
	/// Offset to the next data.
	/// </summary>
	/// <returns>offset</returns>
	auto OffsetToData() const->unsigned int;

	/// <summary>
	/// Offset to the next data.
	/// </summary>
	/// <param name="off">offset</param>
	/// <returns></returns>
	auto OffsetToData(const unsigned int off) -> void;

	/// <summary>
	/// Offset to the next directory.
	/// </summary>
	/// <returns>offset</returns>
	auto OffsetToDirectory() -> unsigned int;

	/// <summary>
	/// True if the entry data is a directory
	/// </summary>
	/// <returns></returns>
	auto DataIsDirectory() -> bool;

	/// <summary>
	/// True if the entry is a resource with a name.
	/// </summary>
	/// <returns></returns>
	auto IsNamedEntry() -> bool;

	/// <summary>
	/// True if the entry is a resource with an ID instead of a name.
	/// </summary>
	/// <returns></returns>
	auto IsIdEntry() -> bool;

	/// <summary>
	/// Resolve the resource identifier of resource entries to a human readable string with a meaning.
	/// </summary>
	/// <param name="id">Resource identifier</param>
	/// <returns>String representation of the ID</returns>
	static auto ResolveResourceId(const unsigned int& id) -> std::string;

private:
	ImageResourceDirectoryEntry() = default;
	ImageResourceDirectoryEntry(const ImageResourceDirectoryEntry&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	std::shared_ptr<ImageResourceDirectory> resourceDirectory;
	std::shared_ptr<ImageResourceDirectory> parent;
	std::string NameResolved;
	long offset;
	long resourceDirectoryOffset;

	friend class PE;
};

/// <summary>
/// The resource directory contains icons, mouse pointer, string language files etc. 
/// which are used by the application.
/// </summary>
class ImageResourceDirectory
{
public:
	ImageResourceDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset,
		const long& resourceDirectoryOffset, const long& resourceDirectoryLength);

	ImageResourceDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset,
		const std::shared_ptr<ImageResourceDirectoryEntry>& parent,
		const long& resourceDirectoryOffset, const long& resourceDirectoryLength);

	ImageResourceDirectory(const ImageResourceDirectory&) = default;

	/// <summary>
	/// Array with the different directory entries.
	/// </summary>
	/// <returns>List of directory entries</returns>
	auto ImageResourceDirectoryEntries() -> std::vector<std::shared_ptr<ImageResourceDirectoryEntry>>;

	/// <summary>
	/// Get Characteristics
	/// </summary>
	/// <returns></returns>
	auto Characteristics() const -> unsigned int;

	/// <summary>
	/// Set Characteristics
	/// </summary>
	/// <param name="characteristics">Characteristics value</param>
	/// <returns></returns>
	auto Characteristics(const unsigned int& characteristics) -> void;

	/// <summary>
	/// Get TimeDateStamp
	/// </summary>
	/// <returns></returns>
	auto TimeDateStamp() const -> unsigned int;

	/// <summary>
	/// Set TimeDateStamp
	/// </summary>
	/// <param name="time">TimeDateStamp value</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& time) -> void;

	/// <summary>
	/// Get MajorVersion
	/// </summary>
	/// <returns></returns>
	auto MajorVersion() const -> unsigned short;

	/// <summary>
	/// Set MajorVersion
	/// </summary>
	/// <param name="majorVersion">MajorVersion value</param>
	/// <returns></returns>
	auto MajorVersion(const unsigned short& majorVersion) -> void;

	/// <summary>
	/// Get MinorVersion
	/// </summary>
	/// <returns></returns>
	auto MinorVersion() const -> unsigned short;

	/// <summary>
	/// Set MinorVersion
	/// </summary>
	/// <param name="minorVersion">MinorVersion value</param>
	/// <returns></returns>
	auto MinorVersion(const unsigned short& minorVersion) -> void;

	/// <summary>
	/// Get NumberOfNameEntries
	/// </summary>
	/// <returns></returns>
	auto NumberOfNameEntries() const -> unsigned short;

	/// <summary>
	/// Set NumberOfNameEntries
	/// </summary>
	/// <param name="nameEntires">NumberOfNameEntries value</param>
	/// <returns></returns>
	auto NumberOfNameEntries(const unsigned short& nameEntires) -> void;

	/// <summary>
	/// Get NumberOfIdEntries
	/// </summary>
	/// <returns></returns>
	auto NumberOfIdEntries() const -> unsigned short;

	/// <summary>
	/// Set NumberOfIdEntries
	/// </summary>
	/// <param name="idEntires">NumberOfIdEntries value</param>
	/// <returns></returns>
	auto NumberOfIdEntries(const unsigned short& idEntires) -> void;

private:
	ImageResourceDirectory() = default;

	auto ParseDirectoryEntries() -> std::vector<std::shared_ptr<ImageResourceDirectoryEntry>>;
	auto SanityCheckFailed(const std::shared_ptr<ImageResourceDirectoryEntry>& entry)->bool;

	// variables
	std::shared_ptr<BufferFile> bFile;
	std::shared_ptr<ImageResourceDirectoryEntry> parent;
	long offset;
	long resourceDirectoryOffset;
	long resourceDirectoryLength;

	friend class PE;
};