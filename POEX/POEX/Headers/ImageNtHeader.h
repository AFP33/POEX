#pragma once

#include "BufferFile.h"
#include "ImageFileHeader.h"
#include "ImageOptionalHeader.h"

namespace POEX
{
	/// <summary>
/// The NT header is the main header for modern Windows applications. It contains the file header and the optional header.
/// </summary>
	class ImageNtHeader
	{
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="bFile">A PE file</param>
		/// <param name="offset">Location of start ImgeNtHeader struct</param>
		ImageNtHeader(const std::shared_ptr<BufferFile>& bFile, const long& offset);
		~ImageNtHeader() = default;

		/// <summary>
		/// Get NT header signature.
		/// </summary>
		/// <returns>NT signature as unsigned int</returns>
		auto Signature() const ->unsigned int;

		/// <summary>
		/// Set NT header signature.
		/// </summary>
		/// <param name="signature">Signature as unsigned int</param>
		/// <returns></returns>
		auto Signature(const unsigned int& signature)->void;

		/// <summary>
		/// Get ImageFileHeader
		/// </summary>
		/// <returns>ImageFileHader object</returns>
		auto FileHeader() const->ImageFileHeader;

		/// <summary>
		/// Get ImageOptionalHeader
		/// </summary>
		/// <returns>ImageOptionalHeader object</returns>
		auto OptionalHeader() const->ImageOptionalHeader;

	private:
		ImageNtHeader() = default;

		// variables
		std::shared_ptr<BufferFile> bFile;
		long offset;

		friend class PE;
	};
}