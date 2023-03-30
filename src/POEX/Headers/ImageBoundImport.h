#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"

/// <summary>
/// Bound import descriptor.
/// </summary>
class ImageBoundImport
{
public:
	/// <summary>
	///  Create a new ImageBoundImport object.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset of the structure in the buffer.</param>
	ImageBoundImport(const std::shared_ptr<BufferFile>& bFile, const long& offset);
	~ImageBoundImport() = default;

	/// <summary>
	/// Time date stamp.
	/// </summary>
	/// <returns>Time date stamp.</returns>
	auto TimeDateStamp() const -> unsigned int;

	/// <summary>
	/// Time date stamp.
	/// </summary>
	/// <param name="time">Time date stamp.</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& time) -> void;

	/// <summary>
	/// Offset module name.
	/// </summary>
	/// <returns>offset</returns>
	auto OffsetModuleName() const -> unsigned short;

	/// <summary>
	/// Offset module name.
	/// </summary>
	/// <param name="offs">offset</param>
	/// <returns></returns>
	auto OffsetModuleName(const unsigned short& offs) -> void;

	/// <summary>
	/// Number of module forwarder references.
	/// </summary>
	/// <returns>counts if moudle forwarder references</returns>
	auto NumberOfModuleForwarderRefs() const -> unsigned short;

	/// <summary>
	/// Number of module forwarder references.
	/// </summary>
	/// <param name="refs">counts if moudle forwarder references</param>
	/// <returns></returns>
	auto NumberOfModuleForwarderRefs(const unsigned short& refs) -> void;

private:
	ImageBoundImport() = default;
	ImageBoundImport(const ImageBoundImport&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
};