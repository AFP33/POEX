#pragma once

#include "BufferFile.h"

namespace POEX
{
	/// <summary>
	/// The File header contains information about the structure and properties of the PE file.
	/// </summary>
	class ImageFileHeader
	{
	public:
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="bFile">A PE file</param>
		/// <param name="offset">Location of start ImageFileHeader struct</param>
		ImageFileHeader(const std::shared_ptr<BufferFile>& bFile, const long& offset);

		/// Destructor
		~ImageFileHeader() = default;

		/// <summary>
		/// Converting MachineType as string
		/// </summary>
		/// <param name="machine">MachineType struct</param>
		/// <returns>MachineType as string</returns>
		auto ToString(MachineType machine)->std::string;

		/// <summary>
		/// Converting FileCharacteristicsType as string
		/// </summary>
		/// <param name="fileCharacteristicsType">FileCharacteristicsType struct</param>
		/// <returns>FileCharacteristicsType as string</returns>
		auto ToString(FileCharacteristicsType fileCharacteristicsType)->std::string;

		/// <summary>
		/// Get the machine (CPU type) the PE file is intended for.
		/// </summary>
		/// <returns>MachineType enum</returns>
		auto Machine() const->MachineType;

		/// <summary>
		/// Set the machine (CPU type) the PE file is intended for.
		/// </summary>
		/// <param name="machine">MachineType enum</param>
		/// <returns></returns>
		auto Machine(MachineType machine)->void;

		/// <summary>
		/// Get The number of sections in the PE file.
		/// </summary>
		/// <returns>number of section</returns>
		auto NumberOfSection() const->unsigned short;

		/// <summary>
		/// Set The number of sections in the PE file.
		/// </summary>
		/// <param name="numberOfSection">number of section</param>
		/// <returns></returns>
		auto NumberOfSection(const unsigned short& numberOfSection)->void;

		/// <summary>
		/// Get Time and date stamp.
		/// </summary>
		/// <returns>time and date as unsigned int</returns>
		auto TimeDateStamp() const->unsigned int;

		/// <summary>
		/// Set Time and date stamp.
		/// </summary>
		/// <param name="timeDateStamp">time and data as unsigned int</param>
		/// <returns></returns>
		auto TimeDateStamp(const unsigned int& timeDateStamp)->void;

		/// <summary>
		/// Get Pointer to COFF symbols table. They are rare in PE files, and often in obj files.
		/// </summary>
		/// <returns>Pointer to Symbol Table</returns>
		auto PointerToSymbolTable() const->unsigned int;

		/// <summary>
		/// Set Pointer to COFF symbols table. They are rare in PE files, and often in obj files.
		/// </summary>
		/// <param name="pointerToSymbolTable">Pointer to Symbol Table</param>
		/// <returns></returns>
		auto PointerToSymbolTable(const unsigned int& pointerToSymbolTable)->void;

		/// <summary>
		/// Get The number of COFF symbols.
		/// </summary>
		/// <returns>number of COFF symbol</returns>
		auto NumberOfSymbols() const->unsigned int;

		/// <summary>
		/// Set The number of COFF symbols.
		/// </summary>
		/// <param name="numberOfSymbols">Number of COFF Symbol</param>
		/// <returns></returns>
		auto NumberOfSymbols(const unsigned int& numberOfSymbols)->void;

		/// <summary>
		/// Get The size of the optional header which follow the file header.
		/// </summary>
		/// <returns>Size of optional Header</returns>
		auto SizeOfOptionalHeader() const->unsigned short;

		/// <summary>
		/// Set The size of the optional header which follow the file header.
		/// </summary>
		/// <param name="sizeOfOptionalHeader">Size of optional Header</param>
		/// <returns></returns>
		auto SizeOfOptionalHeader(const unsigned short& sizeOfOptionalHeader)->void;

		/// <summary>
		/// Get Characteristics flags which describe the PE file in detail.
		/// </summary>
		/// <returns>FileCharacteristicsType enum</returns>
		auto Characteristics() const->FileCharacteristicsType;

		/// <summary>
		/// Set Characteristics flags which describe the PE file in detail.
		/// </summary>
		/// <param name="fileCharacteristicsType">FileCharacteristicsType enum</param>
		/// <returns></returns>
		auto Characteristics(FileCharacteristicsType fileCharacteristicsType)->void;

	private:
		ImageFileHeader() = default;

		// variables
		std::shared_ptr<BufferFile> bFile;
		long offset;

		friend class PE;
		friend class ImageNtHeader;
	};
}

