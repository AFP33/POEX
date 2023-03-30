#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"

/// <summary>
	/// This class represents the IMAGE_SECTION_HEADER structure of image
	/// </summary>
class ImageSectionHeader
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="bFile">A PE file</param>
	/// <param name="offset">Location of start</param>
	/// <param name="imageBaseAddress">Base address of the image from the Optional header</param>
	ImageSectionHeader(const std::shared_ptr<BufferFile>& bFile, const long& offset, const unsigned long& imageBaseAddress);
	//ImageSectionHeader(ImageSectionHeader&&) = default;
	~ImageSectionHeader() = default;

	auto ToString(SectionFlag sectionFlag)->std::string;

	/// <summary>
	/// Get base address of the image from the Optional header.
	/// </summary>
	/// <returns>Base address as unsigned long</returns>
	auto ImageBaseAddress()->unsigned long;

	/// <summary>
	/// Get the section name as a string.
	/// </summary>
	/// <returns>Section name as string</returns>
	auto Name() const->std::string;

	/// <summary>
	/// Set the section name as a string.
	/// </summary>
	/// <param name="name">Section name</param>
	/// <returns></returns>
	auto Name(const std::string& name)->void;

	/// <summary>
	/// Get virtual size of section.
	/// The total size of the section when loaded into memory.
	/// </summary>
	/// <returns>The total size</returns>
	auto VirtualSize() const ->unsigned int;

	/// <summary>
	/// Set virtual size of section.
	/// The total size of the section when loaded into memory.
	/// </summary>
	/// <returns>The total size</returns>
	auto VirtualSize(const unsigned int& virtualSize)->void;

	/// <summary>
	/// Get RVA of the section start in memory.
	/// </summary>
	/// <returns>RVA</returns>
	auto VirtualAddress() const ->unsigned int;

	/// <summary>
	/// Set RVA of the section start in memory.
	/// </summary>
	/// <param name="virtualAddress">RVA</param>
	/// <returns></returns>
	auto VirtualAddress(const unsigned int& virtualAddress)->void;

	/// <summary>
	/// Get size of the section in raw on disk.
	/// Must be a multiple of the file alignment specified in the optional header. 
	/// If its less than the virtual size, the rest is filled with zeros.
	/// </summary>
	/// <returns>Size</returns>
	auto SizeOfRawData() const ->unsigned int;

	/// <summary>
	/// Set size of the section in raw on disk.
	/// Must be a multiple of the file alignment specified in the optional header. 
	/// If its less than the virtual size, the rest is filled with zeros.
	/// </summary>
	/// <param name="sizeOfRawData">Size</param>
	/// <returns></returns>
	auto SizeOfRawData(const unsigned int& sizeOfRawData)->void;

	/// <summary>
	/// Raw address of the section in the file.
	/// </summary>
	/// <returns>Raw address</returns>
	auto PointerToRawData() const ->unsigned int;

	/// <summary>
	/// Raw address of the section in the file.
	/// </summary>
	/// <param name="pointerToRawData">Raw data address</param>
	/// <returns></returns>
	auto PointerToRawData(const unsigned int& pointerToRawData)->void;

	/// <summary>
	/// Get pointer to the beginning of the relocation.
	/// If there are none, the value is zero.
	/// </summary>
	/// <returns>Pointer address</returns>
	auto PointerToRelocations() const ->unsigned int;

	/// <summary>
	/// Set pointer to the beginning of the relocation.
	/// If there are none, the value is zero.
	/// </summary>
	/// <param name="pointerToRelocations">Pointer of relocation</param>
	/// <returns></returns>
	auto PointerToRelocations(const unsigned int& pointerToRelocations)->void;

	/// <summary>
	/// Get pointer to the beginning of the line-numbers in the file.
	/// Zero if there are no line-numbers in the file.
	/// </summary>
	/// <returns>Pointer address</returns>
	auto PointerToLinenumbers() const ->unsigned int;

	/// <summary>
	/// Set pointer to the beginning of the line-numbers in the file.
	/// Zero if there are no line-numbers in the file.
	/// </summary>
	/// <param name="pointerToLinenumbers">Pointer address</param>
	/// <returns></returns>
	auto PointerToLinenumbers(const unsigned int& pointerToLinenumbers)->void;

	/// <summary>
	/// The number of relocations for the section. Is zero for executable images.
	/// </summary>
	/// <returns>Number of relocation</returns>
	auto NumberOfRelocations() const ->unsigned short;

	/// <summary>
	/// The number of relocations for the section. Is zero for executable images.
	/// </summary>
	/// <param name="numberOfRelocations">Number of relocation</param>
	/// <returns></returns>
	auto NumberOfRelocations(const unsigned short& numberOfRelocations)->void;

	/// <summary>
	/// Get the number of line-number entries for the section.
	/// </summary>
	/// <returns>The number of line-number</returns>
	auto NumberOfLinenumbers() const ->unsigned short;

	/// <summary>
	/// Set the number of line-number entries for the section.
	/// </summary>
	/// <param name="numberOfLinenumbers">The number of line-number</param>
	/// <returns></returns>
	auto NumberOfLinenumbers(const unsigned short& numberOfLinenumbers)->void;

	/// <summary>
	/// Section characteristics.
	/// </summary>
	/// <returns>SectionFlag enum</returns>
	auto Characteristics() const->SectionFlag;

	/// <summary>
	/// Section characteristics.
	/// </summary>
	/// <param name="characteristics">SectionFlag</param>
	/// <returns></returns>
	auto Characteristics(const SectionFlag& characteristics)->void;

	/// <summary>
	/// Convert the section header to a byte array with the correct layout for a PE file.
	/// </summary>
	/// <returns>Array of bytes</returns>
	auto ToArray()->std::vector<byte>;

private:
	ImageSectionHeader() = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
	unsigned long imageBaseAddress;

	// functions
	auto FixedNameLength(const std::string& name)->std::vector<byte>;

	friend class PE;
};