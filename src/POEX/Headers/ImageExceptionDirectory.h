#pragma once

#include "BufferFile.h"
#include "ImageSectionHeader.h"
#include "ImageDataDirectory.h"

/// <summary>
/// This struct is represents a function in the exception header for x64 applications.
/// </summary>
struct ExceptionTable
{
	/// <summary>
	/// Get RVA Start of the function in code.
	/// </summary>
	/// <returns></returns>
	auto BeginAddress() const -> unsigned long;

	/// <summary>
	/// Set RVA Start of the function in code.
	/// </summary>
	/// <param name="offset"></param>
	/// <returns></returns>
	auto BeginAddress(const unsigned long& offset) -> void;

	/// <summary>
	/// Get RVA End of the function in code.
	/// </summary>
	/// <returns></returns>
	auto EndAddress() const -> unsigned long;

	/// <summary>
	/// Set RVA End of the function in code.
	/// </summary>
	/// <param name="offset"></param>
	/// <returns></returns>
	auto EndAddress(const unsigned long& offset) -> void;

	/// <summary>
	/// Get Pointer to the unwind information.
	/// </summary>
	/// <returns></returns>
	auto UnwInfo() const -> unsigned long;

	/// <summary>
	/// Set Pointer to the unwind information.
	/// </summary>
	/// <param name="pointer">Pointer to the unwind information</param>
	/// <returns></returns>
	auto UnwInfo(const unsigned long& pointer) ->void;

    ExceptionTable(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
        const std::vector<ImageSectionHeader>& imageSectionHeaders);
    ~ExceptionTable() = default;

private:
    ExceptionTable() = default;
    ExceptionTable(const ExceptionTable&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	std::vector<ImageSectionHeader> imageSectionHeaders;
	long offset;

    friend class PE;
};

/// <summary>
/// The Exception Directory contain all Exception Table Headers
/// </summary>
class ImageExceptionDirectory
{
public:
	ImageExceptionDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset,
		const std::vector<ImageSectionHeader>& imageSectionHeaders,
		const bool& is32Bit, const unsigned int& directorySize);
	~ImageExceptionDirectory() = default;

	/// <summary>
	/// Get all Runtime Function
	/// </summary>
	/// <returns>list of Runtime function</returns>
	auto GetExceptionDirectories() -> std::vector<std::unique_ptr<ExceptionTable>>;

private:
	ImageExceptionDirectory() = default;
	ImageExceptionDirectory(const ImageExceptionDirectory&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	std::vector<ImageSectionHeader> imageSectionHeaders;
	long offset;
	bool is32Bit;
	unsigned int directorySize;

    friend class PE;
};