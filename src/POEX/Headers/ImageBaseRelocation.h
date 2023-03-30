#pragma once

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

#include "BufferFile.h"

struct TypeOffset
{
	/// <summary>
	/// Create a new TypeOffset object.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset of the TypeOffset in the PE file.</param>
	TypeOffset(const std::shared_ptr<BufferFile>& bFile, const long& offset);

	/// <summary>
	/// The type is described in the 4 lower bits of the TypeOffset word.
	/// </summary>
	/// <returns>type</returns>
	auto Type() const->std::string;

	/// <summary>
	/// The offset is described in the 12 higher bits of the TypeOffset word.
	/// </summary>
	/// <returns>offset</returns>
	auto Offset() const->unsigned short;

private:
	TypeOffset() = default;
	TypeOffset(const TypeOffset&) = default;

	auto ParseType(const byte& type) const -> std::string;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
};

/// <summary>
/// The ImageBaseRelocation structure holds information needed to relocate
/// the image to another virtual address.
/// </summary>
class ImageBaseRelocation
{
public:

	/// <summary>
	/// Create a new ImageBaseRelocation object.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset to the relocation struct in the PE file.</param>
	/// <param name="relocationSize">Size of the complete relocation directory.</param>
	ImageBaseRelocation(const std::shared_ptr<BufferFile>& bFile, const long& offset,
		const unsigned int& relocationSize);
	~ImageBaseRelocation() = default;

	/// <summary>
	/// RVA of the relocation block.
	/// </summary>
	/// <returns>RVA</returns>
	auto VirtualAddress() const -> unsigned int;

	/// <summary>
	/// RVA of the relocation block.
	/// </summary>
	/// <param name="va">RVA</param>
	/// <returns></returns>
	auto VirtualAddress(const unsigned int& va) -> void;

	/// <summary>
	/// SizeOfBlock-8 indicates how many TypeOffsets follow the SizeOfBlock.
	/// </summary>
	/// <returns>length</returns>
	auto SizeOfBlock() const -> unsigned int;

	/// <summary>
	/// SizeOfBlock-8 indicates how many TypeOffsets follow the SizeOfBlock.
	/// </summary>
	/// <param name="len">length</param>
	/// <returns></returns>
	auto SizeOfBlock(const unsigned int& len) -> void;

	auto TypeOffsets() -> std::vector<std::unique_ptr<TypeOffset>>;

private:
	ImageBaseRelocation() = default;
	ImageBaseRelocation(const ImageBaseRelocation&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;
	unsigned int relocationSize;
};