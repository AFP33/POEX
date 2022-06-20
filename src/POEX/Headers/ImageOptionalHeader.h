#pragma once

#include "BufferFile.h"
#include "ImageDataDirectory.h"

/// <summary>
/// Represents the optional header in the NT header.
/// </summary>
class ImageOptionalHeader
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="bFile">A PE file</param>
	/// <param name="offset">Location of start optional Header</param>
	/// <param name="is64Bit">represent is file 64bit or 32bit</param>
	ImageOptionalHeader(const std::shared_ptr<BufferFile>& bFile, const long& offset, const bool& is64Bit);
	~ImageOptionalHeader() = default;

	/// <summary>
	/// Converting SubsystemType as string
	/// </summary>
	/// <param name="subsystem">The SubsystemType</param>
	/// <returns>Subsystem as string</returns>
	auto ToString(SubsystemType subsystem)->std::string;
	auto ToString(DllCharacteristicsType dllCharacteristicsType)->std::string;
	auto ToString(FileType fileType)->std::string;

	/// <summary>
	/// Get Data Directories
	/// </summary>
	/// <returns>List of DataDirectory</returns>
	auto DataDirectory()->std::vector<std::unique_ptr<ImageDataDirectory>>;

	/// <summary>
	/// Get magic flag(file is x32, x64 or a ROM image?).
	/// </summary>
	/// <returns>FileType enum</returns>
	auto Magic() const->FileType;

	/// <summary>
	/// Set Magic flag (file is x32, x64 or a ROM image?).
	/// </summary>
	/// <param name="fileType">FileType enum</param>
	/// <returns></returns>
	auto Magic(const FileType& fileType)->void;

	/// <summary>
	/// Get Major linker version.
	/// </summary>
	/// <returns>Major linker version.</returns>
	auto MajorLinkerVersion() const->byte;

	/// <summary>
	/// Set Major linker version.
	/// </summary>
	/// <param name="mlVersion">Major linker version.</param>
	/// <returns></returns>
	auto MajorLinkerVersion(const byte& mlVersion);

	/// <summary>
	/// Get Minor linker version.
	/// </summary>
	/// <returns>Minor linker version.</returns>
	auto MinorLinkerVersion() const->byte;

	/// <summary>
	/// Set Minor linker version.
	/// </summary>
	/// <param name="mlVersion">Minor linker version.</param>
	/// <returns></returns>
	auto MinorLinkerVersion(const byte& mlVersion);

	/// <summary>
	/// Get Size of all code sections together.
	/// </summary>
	/// <returns>Size of Code</returns>
	auto SizeOfCode() const->unsigned int;

	/// <summary>
	/// Set Size of all code sections together.
	/// </summary>
	/// <param name="sizeOfCode">Size of Code</param>
	/// <returns></returns>
	auto SizeOfCode(const unsigned int& sizeOfCode)-> void;

	/// <summary>
	/// Get Size of all initialized data sections together.
	/// </summary>
	/// <returns>Size of initilized data</returns>
	auto SizeOfInitializedData() const->unsigned int;

	/// <summary>
	/// Set Size of all initialized data sections together.
	/// </summary>
	/// <param name="sizeOfInitializedData">Size of initilized data</param>
	/// <returns></returns>
	auto SizeOfInitializedData(const unsigned int& sizeOfInitializedData)->void;

	/// <summary>
	/// Get Size of all uninitialized data sections together.
	/// </summary>
	/// <returns>Size of uninitialized data</returns>
	auto SizeOfUninitializedData() const->unsigned int;

	/// <summary>
	/// Set Size of all uninitialized data sections together.
	/// </summary>
	/// <param name="sizeOfUninitializedData">Size of uninitialized data</param>
	/// <returns></returns>
	auto SizeOfUninitializedData(const unsigned int& sizeOfUninitializedData)->void;

	/// <summary>
	/// Get RVA of the entry point function.
	/// </summary>
	/// <returns>RVA of the entry point function.</returns>
	auto AddressOfEntryPoint() const->unsigned int;

	/// <summary>
	/// Set RVA of the entry point function.
	/// </summary>
	/// <param name="addressOfEntryPoint">RVA of the entry point function.</param>
	/// <returns></returns>
	auto AddressOfEntryPoint(const unsigned int& addressOfEntryPoint)->void;

	/// <summary>
	/// Get RVA to the beginning of the code section.
	/// </summary>
	/// <returns>RVA to the beginning of the code section.</returns>
	auto BaseOfCode() const->unsigned int;

	/// <summary>
	/// Set RVA to the beginning of the code section.
	/// </summary>
	/// <param name="baseOfCode">RVA to the beginning of the code section.</param>
	/// <returns></returns>
	auto BaseOfCode(const unsigned int& baseOfCode)->void;

	/// <summary>
	/// Get RVA to the beginning of the data section.
	/// </summary>
	/// <returns>RVA to the beginning of the data section.</returns>
	auto BaseOfData() const->unsigned int;

	/// <summary>
	/// Set RVA to the beginning of the data section.
	/// </summary>
	/// <param name="baseOfData">RVA to the beginning of the data section.</param>
	/// <returns></returns>
	auto BaseOfData(const unsigned int& baseOfData)->void;

	/// <summary>
	/// Get Preferred address of the image when it's loaded to memory.
	/// </summary>
	/// <returns>Preferred address of the image when it's loaded to memory.</returns>
	auto ImageBase() const ->unsigned long;

	/// <summary>
	/// Set Preferred address of the image when it's loaded to memory.
	/// </summary>
	/// <param name="imageBase">Preferred address of the image when it's loaded to memory.</param>
	/// <returns></returns>
	auto ImageBase(const unsigned long& imageBase)->void;

	/// <summary>
	/// Get Section alignment in memory in bytes. Must be greater or equal to the file alignment.
	/// </summary>
	/// <returns>Section alignment in memory in bytes.</returns>
	auto SectionAlignment() const->unsigned int;

	/// <summary>
	/// Set Section alignment in memory in bytes. Must be greater or equal to the file alignment.
	/// </summary>
	/// <param name="sectionAlignment">Section alignment in memory in bytes.</param>
	/// <returns></returns>
	auto SectionAlignment(const unsigned int& sectionAlignment)->void;

	/// <summary>
	/// Get File alignment of the raw data of the sections in bytes.
	/// </summary>
	/// <returns>File alignment of the raw data of the sections in bytes.</returns>
	auto FileAlignment() const->unsigned int;

	/// <summary>
	/// Set File alignment of the raw data of the sections in bytes.
	/// </summary>
	/// <param name="fileAlignment">File alignment of the raw data of the sections in bytes.</param>
	/// <returns></returns>
	auto FileAlignment(const unsigned int& fileAlignment)->void;

	/// <summary>
	/// Get Major operation system version to run the file.
	/// </summary>
	/// <returns>Major operation system version to run the file.</returns>
	auto MajorOperatingSystemVersion() const->unsigned short;

	/// <summary>
	/// Set Major operation system version to run the file.
	/// </summary>
	/// <param name="majorOperatingSystemVersion">Major operation system version to run the file.</param>
	/// <returns></returns>
	auto MajorOperatingSystemVersion(const unsigned short& majorOperatingSystemVersion)->void;

	/// <summary>
	/// Get Minor operation system version to run the file.
	/// </summary>
	/// <returns>Minor operation system version to run the file.</returns>
	auto MinorOperatingSystemVersion() const->unsigned short;

	/// <summary>
	/// Set Minor operation system version to run the file.
	/// </summary>
	/// <param name="minorOperatingSystemVersion">Minor operation system version to run the file.</param>
	/// <returns></returns>
	auto MinorOperatingSystemVersion(const unsigned short& minorOperatingSystemVersion)->void;

	/// <summary>
	/// Get Major Image Version
	/// </summary>
	/// <returns>Major Image Version</returns>
	auto MajorImageVersion() const->unsigned short;

	/// <summary>
	/// Set Major Image Version
	/// </summary>
	/// <param name="majorImageVersion">Major Image Version</param>
	/// <returns></returns>
	auto MajorImageVersion(const unsigned short& majorImageVersion)->void;

	/// <summary>
	/// Get Minor Image Version
	/// </summary>
	/// <returns>Minor Image Version</returns>
	auto MinorImageVersion() const->unsigned short;

	/// <summary>
	/// Set Minor Image Version
	/// </summary>
	/// <param name="minorImageVersion">Minor Image Version</param>
	/// <returns></returns>
	auto MinorImageVersion(const unsigned short& minorImageVersion)->void;

	/// <summary>
	/// Get Major version of the subsystem.
	/// </summary>
	/// <returns>Major version of the subsystem.</returns>
	auto MajorSubsystemVersion() const->unsigned short;

	/// <summary>
	/// Set Major version of the subsystem.
	/// </summary>
	/// <param name="majorSubsystemVersion">Major version of the subsystem.</param>
	/// <returns></returns>
	auto MajorSubsystemVersion(const unsigned short& majorSubsystemVersion)->void;

	/// <summary>
	/// Get Minor version of the subsystem.
	/// </summary>
	/// <returns>Minor version of the subsystem.</returns>
	auto MinorSubsystemVersion() const->unsigned short;

	/// <summary>
	/// Set Minor version of the subsystem.
	/// </summary>
	/// <param name="minorSubsystemVersion">Minor version of the subsystem.</param>
	/// <returns></returns>
	auto MinorSubsystemVersion(const unsigned short& minorSubsystemVersion)->void;

	/// <summary>
	/// Reserved, must be 0.
	/// </summary>
	/// <returns>0</returns>
	auto Win32VersionValue() const->unsigned int;

	/// <summary>
	/// Reserved, must be 0.
	/// </summary>
	/// <param name="win32VersionValue">0</param>
	/// <returns></returns>
	auto Win32VersionValue(const unsigned int& win32VersionValue = 0)->void;

	/// <summary>
	/// Get Size of the image including all headers in bytes. Must be a multiple of the section alignment.
	/// </summary>
	/// <returns>Size of the image including all headers in bytes.</returns>
	auto SizeOfImage() const->unsigned int;

	/// <summary>
	/// Set Size of the image including all headers in bytes. Must be a multiple of the section alignment.
	/// </summary>
	/// <param name="sizeOfImage">Size of the image including all headers in bytes.</param>
	/// <returns></returns>
	auto SizeOfImage(const unsigned int& sizeOfImage)->void;

	/// <summary>
	/// Get Sum of the e_lfanwe from the DOS header, the 4 byte signature, size of the file header, size of the optional header and size of all section. Rounded to the next file alignment.
	/// </summary>
	/// <returns>Size of Header</returns>
	auto SizeOfHeaders() const->unsigned int;

	/// <summary>
	/// Set Sum of the e_lfanwe from the DOS header, the 4 byte signature, size of the file header, size of the optional header and size of all section. Rounded to the next file alignment.
	/// </summary>
	/// <param name="sizeOfHeaders">Sum of the e_lfanwe from the DOS header, the 4 byte signature, size of the file header, size of the optional header and size of all section.</param>
	/// <returns></returns>
	auto SizeOfHeaders(const unsigned int& sizeOfHeaders)->void;

	/// <summary>
	/// Get Image checksum validated at runtime for drivers, DLLs loaded at boot time and DLLs loaded into a critical system.
	/// </summary>
	/// <returns>Image checksum validated at runtime for drivers, DLLs loaded at boot time and DLLs loaded into a critical system.</returns>
	auto CheckSum() const->unsigned int;

	/// <summary>
	/// Set Image checksum validated at runtime for drivers, DLLs loaded at boot time and DLLs loaded into a critical system.
	/// </summary>
	/// <param name="checkSum">Image checksum validated at runtime for drivers, DLLs loaded at boot time and DLLs loaded into a critical system.</param>
	/// <returns></returns>
	auto CheckSum(const unsigned int& checkSum)->void;

	/// <summary>
	/// Get The subsystem required to run the image e.g., Windows GUI, XBOX etc.
	/// </summary>
	/// <returns>SubsystemType Enum</returns>
	auto Subsystem() const->SubsystemType;

	/// <summary>
	/// Set The subsystem required to run the image e.g., Windows GUI, XBOX etc.
	/// </summary>
	/// <param name="systemType">SystemType enum</param>
	/// <returns></returns>
	auto Subsystem(const SubsystemType& systemType)->void;

	/// <summary>
	/// Get DLL characteristics of the image.
	/// </summary>
	/// <returns>DllCharacteristicsType enum</returns>
	auto DllCharacteristics() const->DllCharacteristicsType;

	/// <summary>
	/// Set Get DLL characteristics of the image.
	/// </summary>
	/// <param name="dllCharacteristicsType">DllCharacteristicsType enum</param>
	/// <returns></returns>
	auto DllCharacteristics(const DllCharacteristicsType& dllCharacteristicsType)->void;

	/// <summary>
	/// Get Size of stack reserve in bytes.
	/// </summary>
	/// <returns>Size of stack reserve in bytes.</returns>
	auto SizeOfStackReserve() const->unsigned long;

	/// <summary>
	/// Set Size of stack reserve in bytes.
	/// </summary>
	/// <param name="sizeOfStackReserve">Size of stack reserve in bytes.</param>
	/// <returns></returns>
	auto SizeOfStackReserve(const unsigned long& sizeOfStackReserve)->void;

	/// <summary>
	/// Get Size of bytes committed for the stack in bytes.
	/// </summary>
	/// <returns>Size of bytes committed for the stack in bytes.</returns>
	auto SizeOfStackCommit() const->unsigned long;

	/// <summary>
	/// Set Size of bytes committed for the stack in bytes.
	/// </summary>
	/// <param name="sizeOfStackCommit">Size of bytes committed for the stack in bytes.</param>
	/// <returns></returns>
	auto SizeOfStackCommit(const unsigned long& sizeOfStackCommit)->void;

	/// <summary>
	/// Get Size of the heap to reserve in bytes.
	/// </summary>
	/// <returns>Size of the heap to reserve in bytes.</returns>
	auto SizeOfHeapReserve() const->unsigned long;

	/// <summary>
	/// Set Size of the heap to reserve in bytes.
	/// </summary>
	/// <param name="sizeOfHeapReserve">Size of the heap to reserve in bytes.</param>
	/// <returns></returns>
	auto SizeOfHeapReserve(const unsigned long& sizeOfHeapReserve)->void;

	/// <summary>
	/// Get Size of the heap commit in bytes.
	/// </summary>
	/// <returns>Size of the heap commit in bytes.</returns>
	auto SizeOfHeapCommit() const->unsigned long;

	/// <summary>
	/// Set Size of the heap commit in bytes.
	/// </summary>
	/// <param name="sizeOfHeapCommit">Size of the heap commit in bytes.</param>
	/// <returns></returns>
	auto SizeOfHeapCommit(const unsigned long& sizeOfHeapCommit)->void;

	/// <summary>
	/// Get Obsolete
	/// </summary>
	/// <returns>Obsolete</returns>
	auto LoaderFlags() const->unsigned int;

	/// <summary>
	/// Set Obsolete
	/// </summary>
	/// <param name="loaderFlags">Obsolete</param>
	/// <returns></returns>
	auto LoaderFlags(const unsigned int& loaderFlags)->void;

	/// <summary>
	/// Get Number of directory entries in the remainder of the optional header.
	/// </summary>
	/// <returns>Number of directory entries in the remainder of the optional header.</returns>
	auto NumberOfRvaAndSizes() const->unsigned int;

	/// <summary>
	/// Set Number of directory entries in the remainder of the optional header.
	/// </summary>
	/// <param name="numberOfRvaAndSizes">Number of directory entries in the remainder of the optional header.</param>
	/// <returns></returns>
	auto NumberOfRvaAndSizes(const unsigned int& numberOfRvaAndSizes)->void;

private:
	ImageOptionalHeader() = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
	bool is64Bit;

	friend class PE;
	friend class ImageNtHeader;
};