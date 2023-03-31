#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"
#include "ImageSectionHeader.h"
#include "ImageDataDirectory.h"

struct ExportFunction
{
	/// <summary>
	/// function name
	/// </summary>
	std::string Name;

	/// <summary>
	/// function RVA
	/// </summary>
	unsigned int Address;

	/// <summary>
	/// function ordinal
	/// </summary>
	unsigned short Ordinal;

	/// <summary>
	/// function name if the function is forwarded to another DLL.
	/// </summary>
	std::string ForwardedName;

	/// <summary>
	/// New Export Function
	/// </summary>
	/// <param name="name">Function name</param>
	/// <param name="address">Function address</param>
	/// <param name="ordinal">Function ordinal</param>
	ExportFunction(const std::string& name, const unsigned int& address, const unsigned short& ordinal) : 
		Name(name), Address(address), Ordinal(ordinal) {};

	/// <summary>
	/// New Export Function
	/// </summary>
	/// <param name="name">Function name</param>
	/// <param name="address">Function address</param>
	/// <param name="ordinal">Function ordinal</param>
	/// <param name="forwardedName">Function Forward name</param>
	ExportFunction(const std::string& name, const unsigned int& address, const unsigned short& ordinal, const std::string& forwardedName) :
		Name(name), Address(address), Ordinal(ordinal), ForwardedName(forwardedName) {};
};

/// <summary>
/// The export directory contains all exported function, symbols and etc. which can be used by other module.
/// </summary>
class ImageExportDirectory
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="bFile">A PE file</param>
	/// <param name="offset">Location of export directory in PE file</param>
	ImageExportDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
		const std::vector<std::shared_ptr<ImageSectionHeader>>& imageSectionHeaders, std::unique_ptr<ImageDataDirectory> imageDataDirectory);
	ImageExportDirectory(const ImageExportDirectory&) = default;
	~ImageExportDirectory() = default;

	/// <summary>
	/// Get The characteristics of the export directory.
	/// </summary>
	/// <returns>The characteristics of the export directory.</returns>
	auto Characteristics() const ->unsigned int;

	/// <summary>
	/// Set The characteristics of the export directory.
	/// </summary>
	/// <param name="characteristics">The characteristics of the export directory.</param>
	/// <returns></returns>
	auto Characteristics(const unsigned int& characteristics)->void;

	/// <summary>
	/// Get Time and date stamp.
	/// </summary>
	/// <returns>Time and date stamp.</returns>
	auto TimeDateStamp() const ->unsigned int;

	/// <summary>
	/// Set Time and date stamp.
	/// </summary>
	/// <param name="timeDateStamp">Time and date stamp.</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& timeDateStamp)->void;

	/// <summary>
	/// Get Major Version
	/// </summary>
	/// <returns>Major Version</returns>
	auto MajorVersion() const ->unsigned short;

	/// <summary>
	/// Set Major Version
	/// </summary>
	/// <param name="majorVersion">Major Version</param>
	/// <returns></returns>
	auto MajorVersion(const unsigned short& majorVersion)->void;

	/// <summary>
	/// Get Minor Version
	/// </summary>
	/// <returns>Minor Version</returns>
	auto MinorVersion() const ->unsigned short;

	/// <summary>
	/// Set Minor Version
	/// </summary>
	/// <param name="minorVersion">Minor Version.</param>
	/// <returns></returns>
	auto MinorVersion(const unsigned short& minorVersion)->void;

	/// <summary>
	/// Get Name
	/// </summary>
	/// <returns>name</returns>
	auto Name() const ->unsigned int;

	/// <summary>
	/// Set Name
	/// </summary>
	/// <param name="name">name</param>
	/// <returns></returns>
	auto Name(const unsigned int& name)->void;

	/// <summary>
	/// Get base
	/// </summary>
	/// <returns>base</returns>
	auto Base() const ->unsigned int;

	/// <summary>
	/// Set base
	/// </summary>
	/// <param name="base">base</param>
	/// <returns></returns>
	auto Base(const unsigned int& base)->void;

	/// <summary>
	/// Get Number of exported functions.
	/// </summary>
	/// <returns>Number of exported functions.</returns>
	auto NumberOfFunctions() const ->unsigned int;

	/// <summary>
	/// Set Number of exported functions.
	/// </summary>
	/// <param name="numberOfFunctions">Number of exported functions.</param>
	/// <returns></returns>
	auto NumberOfFunctions(const unsigned int& numberOfFunctions)->void;

	/// <summary>
	/// Get Number of exported names.
	/// </summary>
	/// <returns>Number of exported names.</returns>
	auto NumberOfNames() const ->unsigned int;

	/// <summary>
	/// Set Number of exported names.
	/// </summary>
	/// <param name="numberOfNames">Number of exported names.</param>
	/// <returns></returns>
	auto NumberOfNames(const unsigned int& numberOfNames)->void;

	/// <summary>
	/// Get RVA to the addresses of the functions
	/// </summary>
	/// <returns>RVA to the addresses of the functions</returns>
	auto AddressOfFunctions() const ->unsigned int;

	/// <summary>
	/// Set RVA to the addresses of the functions
	/// </summary>
	/// <param name="addressOfFunctions">RVA to the addresses of the functions</param>
	/// <returns></returns>
	auto AddressOfFunctions(const unsigned int& addressOfFunctions)->void;

	/// <summary>
	/// Get RVA to the addresses of the names
	/// </summary>
	/// <returns>RVA to the addresses of the names</returns>
	auto AddressOfNames() const ->unsigned int;

	/// <summary>
	/// Set RVA to the addresses of the names
	/// </summary>
	/// <param name="addressOfNames">RVA to the addresses of the names.</param>
	/// <returns></returns>
	auto AddressOfNames(const unsigned int& addressOfNames)->void;

	/// <summary>
	/// Get RVA to the name ordinals
	/// </summary>
	/// <returns>RVA to the name ordinals</returns>
	auto AddressOfNameOrdinals() const ->unsigned int;

	/// <summary>
	/// Set RVA to the name ordinals
	/// </summary>
	/// <param name="addressOfNameOrdinals">RVA to the name ordinals</param>
	/// <returns></returns>
	auto AddressOfNameOrdinals(const unsigned int& addressOfNameOrdinals)->void;

	/// <summary>
	/// Parser for retrieve Export Functions 
	/// </summary>
	/// <returns>List of export function as ExportFunction structure</returns>
	auto GetExportFunctions()->std::vector<ExportFunction>;

private:
	ImageExportDirectory() = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	std::vector<std::shared_ptr<ImageSectionHeader>> imageSectionHeaders;
	std::unique_ptr<ImageDataDirectory> imageDataDirectory;
	long offset;

	auto IsForwardedExport(const unsigned int& address) -> bool;

	friend class PE;
};