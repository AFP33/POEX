#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"
#include "ImageSectionHeader.h"
#include "ImageDataDirectory.h"

struct ImportFunction
{
	/// <summary>
	/// Function name.
	/// </summary>
	std::string Name;

	/// <summary>
	/// DLL where the function comes from.
	/// </summary>
	std::string Dll;

	/// <summary>
	/// Function hint.
	/// </summary>
	unsigned short Hint;

	/// <summary>
	/// Offset into the Import Address Table.
	/// </summary>
	unsigned int IATOffset;

	ImportFunction(const std::string& name, const std::string& dll, const unsigned short& hint, const unsigned int iatOffset) :
		Name(name), Dll(dll), Hint(hint), IATOffset(iatOffset) {};
};

class ImageImportDirectory
{
public:
	ImageImportDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset,
		const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders, const unsigned int& iatVirtualSize,
		bool is64Bit);
	~ImageImportDirectory() = default;

	/// <summary>
	/// Get the RVA of the import lookup table. This table contains a name or ordinal for each import.
	/// </summary>
	/// <returns>The RVA as unsigned int(4 bytes)</returns>
	auto ImportLookupTable() const ->unsigned int;

	/// <summary>
	/// Set the RVA of the import lookup table. This table contains a name or ordinal for each import.
	/// </summary>
	/// <param name="originalFirstThunk">The RVA as unsigned int(4 bytes)</param>
	/// <returns></returns>
	auto ImportLookupTable(const unsigned int& importLookupTable)->void;

	/// <summary>
	/// Get the stamp that is set to zero until the image is bound. After the image is bound, this field is set to the time/data stamp of the DLL.
	/// </summary>
	/// <returns>Time and date stamp.</returns>
	auto TimeDateStamp() const ->unsigned int;

	/// <summary>
	/// Set the stamp that is set to zero until the image is bound. After the image is bound, this field is set to the time/data stamp of the DLL.
	/// </summary>
	/// <param name="timeDateStamp">Time and date stamp.</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& timeDateStamp)->void;

	/// <summary>
	/// Get the index of the first forwarder reference.
	/// </summary>
	/// <returns>First forwarder reference</returns>
	auto ForwarderChain() const ->unsigned int;

	/// <summary>
	/// Set the index of the first forwarder reference.
	/// </summary>
	/// <param name="forwarderChain">First forwarder reference</param>
	/// <returns></returns>
	auto ForwarderChain(const unsigned int& forwarderChain)->void;

	/// <summary>
	/// Get Name. The address of an ASCII string that contains the name of the DLL. This address is relative to the image base.
	/// </summary>
	/// <returns>name</returns>
	auto Name() const ->unsigned int;

	/// <summary>
	/// Set Name. The address of an ASCII string that contains the name of the DLL. This address is relative to the image base.
	/// </summary>
	/// <param name="name">name</param>
	/// <returns></returns>
	auto Name(const unsigned int& name)->void;

	/// <summary>
	/// Get the RVA of the import address table. 
	/// The contents of this table are identical to the contents of the import lookup table until the image is bound.
	/// </summary>
	/// <returns>The RVA of the import address table</returns>
	auto ImportAddressTable() const ->unsigned int;

	/// <summary>
	/// Set the RVA of the import address table. 
	/// The contents of this table are identical to the contents of the import lookup table until the image is bound.
	/// </summary>
	/// <param name="firstThunk">The RVA of the import address table</param>
	/// <returns></returns>
	auto ImportAddressTable(const unsigned int& importAddressTable)->void;

	/// <summary>
	/// Get List of Imported function of current Directory
	/// </summary>
	/// <returns></returns>
	auto GetImportedFunctions()->std::vector<ImportFunction>;

private:
	ImageImportDirectory() = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	std::vector<std::shared_ptr<ImageSectionHeader>> imageSectionHeaders;
	unsigned int iatVirtualSize;
	long offset;
	bool is64Bit;

	friend class PE;
};