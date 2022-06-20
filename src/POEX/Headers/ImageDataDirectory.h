#pragma once

#include "BufferFile.h"

/// <summary>
	/// The ImageDataDirectory struct represents the data directory of image
	/// </summary>
class ImageDataDirectory
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="bFile">A PE file</param>
	/// <param name="offset">Location of start specific Data Directory</param>
	/// <param name="dataDirectoryType">Type of Data Directory</param>
	ImageDataDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, const DataDirectoryType& dataDirectoryType);
	~ImageDataDirectory() = default;

	/// <summary>
	/// Get RVA of current Data Directory.
	/// </summary>
	/// <returns>RVA as unsigned int</returns>
	auto VirtualAddress() const->unsigned int;

	/// <summary>
	/// Set RVA of current Data Directory.
	/// </summary>
	/// <param name="virtualAddress">RVA as unsigned int</param>
	/// <returns></returns>
	auto VirtualAddress(const unsigned int& virtualAddress)->void;

	/// <summary>
	/// Get size of current Data Directory in bytes.
	/// </summary>
	/// <returns>Size of Data Directory</returns>
	auto Size() const->unsigned int;

	/// <summary>
	/// Set size of current Data Directory in bytes.
	/// </summary>
	/// <param name="size">Size of Data Directory in bytes</param>
	/// <returns></returns>
	auto Size(const unsigned int& size)->void;

private:
	ImageDataDirectory() = default;

	// variables
	DataDirectoryType dataDirectoryType;
	std::shared_ptr<BufferFile> bFile;
	long offset;
};

