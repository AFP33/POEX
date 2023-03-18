#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"

/// <summary>
/// The ImageDelayImportDirectory describes delayed imports.
/// </summary>
class ImageDelayImportDescriptor
{
public:
	/// <summary>
	/// Create a new ImageDelayImportDirectory object.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset to the delay import descriptor.</param>
	ImageDelayImportDescriptor(const std::shared_ptr<BufferFile>& bFile, 
		const long& offset);
	~ImageDelayImportDescriptor() = default;

	/// <summary>
	/// RVA to Attribute
	/// </summary>
	/// <returns>RVA offset</returns>
	auto Attributes() const-> unsigned int;

	/// <summary>
	/// RVA to Attribute
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto Attributes(const unsigned int& off) -> void;

	/// <summary>
	/// RVA to the name of the target library (NULL-terminate ASCII string)
	/// </summary>
	/// <returns>RVA offset</returns>
	auto DllNameRVA() const-> unsigned int;

	/// <summary>
	/// RVA to the name of the target library (NULL-terminate ASCII string)
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto DllNameRVA(const unsigned int& off) -> void;

	/// <summary>
	/// RVA to the HMODULE caching location (PHMODULE)
	/// </summary>
	/// <returns>RVA offset</returns>
	auto ModuleHandleRVA() const-> unsigned int;

	/// <summary>
	/// RVA to the HMODULE caching location (PHMODULE)
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto ModuleHandleRVA(const unsigned int& off) -> void;

	/// <summary>
	/// RVA to the start of the IAT (PIMAGE_THUNK_DATA)
	/// </summary>
	/// <returns>RVA offset</returns>
	auto ImportAddressTableRVA() const-> unsigned int;

	/// <summary>
	/// RVA to the start of the IAT (PIMAGE_THUNK_DATA)
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto ImportAddressTableRVA(const unsigned int& off) -> void;

	/// <summary>
	/// RVA to the start of the name table (PIMAGE_THUNK_DATA::AddressOfData)
	/// </summary>
	/// <returns>RVA offset</returns>
	auto ImportNameTableRVA() const-> unsigned int;

	/// <summary>
	/// RVA to the start of the name table (PIMAGE_THUNK_DATA::AddressOfData)
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto ImportNameTableRVA(const unsigned int& off) -> void;

	/// <summary>
	/// RVA to an optional bound IAT
	/// </summary>
	/// <returns>RVA offset</returns>
	auto BoundImportAddressTableRVA() const-> unsigned int;

	/// <summary>
	/// RVA to an optional bound IAT
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto BoundImportAddressTableRVA(const unsigned int& off) -> void;

	/// <summary>
	/// RVA to an optional unload info table
	/// </summary>
	/// <returns>RVA offset</returns>
	auto UnloadInformationTableRVA() const-> unsigned int;

	/// <summary>
	/// RVA to an optional unload info table
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto UnloadInformationTableRVA(const unsigned int& off) -> void;

	/// <summary>
	/// 0 if not bound, Otherwise, date/time of the target DLL
	/// </summary>
	/// <returns>RVA offset</returns>
	auto TimeDateStamp() const-> unsigned int;

	/// <summary>
	/// 0 if not bound, Otherwise, date/time of the target DLL
	/// </summary>
	/// <param name="off">RVA offset</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& off) -> void;

private:
	ImageDelayImportDescriptor(const ImageDelayImportDescriptor&) = default;
	ImageDelayImportDescriptor() = default;

	std::shared_ptr<BufferFile> bFile;
	long offset;
};