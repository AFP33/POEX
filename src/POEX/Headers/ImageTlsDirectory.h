#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"
#include "ImageSectionHeader.h"

/// <summary>
/// Thread Local Storage callback.
/// </summary>
struct ImageTlsCallback
{
	/// <summary>
	/// Create a new TLS callback structure.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset to TLS structure in buffer.</param>
	/// <param name="is64Bit">Flag if the PE file is 64 Bit.</param>
	ImageTlsCallback(const std::shared_ptr<BufferFile>& bFile, const long& offset, const bool& is64Bit);
	ImageTlsCallback(const ImageTlsCallback&) = default;

	/// <summary>
	/// Address of actual callback code.
	/// </summary>
	/// <returns>Address of actual callback code.</returns>
	auto Callback() const -> unsigned long;

	/// <summary>
	/// Address of actual callback code.
	/// </summary>
	/// <param name="off">Address of actual callback code.</param>
	/// <returns></returns>
	auto Callback(const unsigned long& off) -> void;

private:
	ImageTlsCallback() = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
	bool is64Bit;
};

/// <summary>
/// Thread Local Storage Directory.
/// </summary>
class ImageTlsDirectory
{
public:

	/// <summary>
	/// Create new TLS directory structure.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset to TLS structure in buffer.</param>
	/// <param name="is64Bit">Flag if the PE file is 64 Bit.</param>
	ImageTlsDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset,
		const std::vector<ImageSectionHeader>& imageSectionHeaders, const bool& is64Bit);

	auto Callbacks() -> std::vector<ImageTlsCallback>;

	/// <summary>
	/// Start address of the raw data.
	/// </summary>
	/// <returns>offset</returns>
	auto StartAddressOfRawData() const -> unsigned long;

	/// <summary>
	/// Start address of the raw data.
	/// </summary>
	/// <param name="off">offset</param>
	/// <returns></returns>
	auto StartAddressOfRawData(const unsigned long& off) -> void;

	/// <summary>
	/// End address of the raw data.
	/// </summary>
	/// <returns>offset</returns>
	auto EndAddressOfRawData() const -> unsigned long;

	/// <summary>
	/// End address of the raw data.
	/// </summary>
	/// <param name="off">offset</param>
	/// <returns></returns>
	auto EndAddressOfRawData(const unsigned long& off) -> void;

	/// <summary>
	/// Address of index (pointer to TLS index).
	/// </summary>
	/// <returns>pointer to TLS index</returns>
	auto AddressOfIndex() const -> unsigned long;

	/// <summary>
	/// Address of index (pointer to TLS index).
	/// </summary>
	/// <param name="off">pointer to TLS index</param>
	/// <returns></returns>
	auto AddressOfIndex(const unsigned long& off) -> void;

	/// <summary>
	/// Address of the callbacks.
	/// </summary>
	/// <returns>Callbacks offset</returns>
	auto AddressOfCallBacks() const -> unsigned long;
	
	/// <summary>
	/// Address of the callbacks.
	/// </summary>
	/// <param name="off">Callbacks offset</param>
	/// <returns></returns>
	auto AddressOfCallBacks(const unsigned long& off) -> void;

	/// <summary>
	/// Size of zero fill.
	/// </summary>
	/// <returns>Zero fill length</returns>
	auto SizeOfZeroFill() const -> unsigned int;

	/// <summary>
	/// Size of zero fill.
	/// </summary>
	/// <param name="length">Zero fill length</param>
	/// <returns></returns>
	auto SizeOfZeroFill(const unsigned int& length) -> void;

	/// <summary>
	/// Characteristics
	/// </summary>
	/// <returns>Characteristics</returns>
	auto Characteristics() const -> unsigned int;

	/// <summary>
	/// Characteristics
	/// </summary>
	/// <param name="characteristics">Characteristics</param>
	/// <returns></returns>
	auto Characteristics(const unsigned int& characteristics) -> void;

private:
	ImageTlsDirectory() = default;
	ImageTlsDirectory(const ImageTlsDirectory&) = default;

	// variables
	std::vector<ImageSectionHeader> imageSectionHeaders;
	std::shared_ptr<BufferFile> bFile;
	long offset;
	bool is64Bit;
};