#pragma once

#include "BufferFile.h"

/// <summary>
/// The ImageDosHeader with which every PE file starts.
/// </summary>
class ImageDosHeader
{
public:

	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="bFile">A PE file</param>
	/// <param name="offset">Location of start ImageDosHeader structure</param>
	ImageDosHeader(const std::shared_ptr<BufferFile>& bFile, const long& offset = 0x000000);
	~ImageDosHeader() = default;

	/// <summary>
	/// Get magic value ("MZ" header).
	/// </summary>
	/// <returns>The magic value</returns>
	auto E_magic() const ->unsigned short;

	/// <summary>
	/// Set magic value
	/// </summary>
	/// <param name="magic">The magic value</param>
	/// <returns></returns>
	auto E_magic(const unsigned short& magic)->void;

	/// <summary>
	/// Get Bytes on the last page of the file.
	/// </summary>
	/// <returns>Size of bytes</returns>
	auto E_cblp() const ->unsigned short;

	/// <summary>
	/// Set Bytes on the last page of the file.
	/// </summary>
	/// <param name="cblp">Size of bytes</param>
	/// <returns></returns>
	auto E_cblp(const unsigned short& cblp)->void;

	/// <summary>
	/// Get Pages in the file.
	/// </summary>
	/// <returns>Number of pages</returns>
	auto E_cp() const ->unsigned short;

	/// <summary>
	/// Set Pages in the file.
	/// </summary>
	/// <param name="cp">Number of pages</param>
	/// <returns></returns>
	auto E_cp(const unsigned short& cp)->void;

	/// <summary>
	/// Get Relocations.
	/// </summary>
	/// <returns>Relocations</returns>
	auto E_crlc() const ->unsigned short;

	/// <summary>
	/// Set Relocations.
	/// </summary>
	/// <param name="crlc">Relocations</param>
	/// <returns></returns>
	auto E_crlc(const unsigned short& crlc)->void;

	/// <summary>
	/// Get size of the header in paragraphs.
	/// </summary>
	/// <returns>Size of header</returns>
	auto E_cparhdr() const ->unsigned short;

	/// <summary>
	/// Set size of the header in paragraphs.
	/// </summary>
	/// <param name="cparhdr">Size of header</param>
	/// <returns></returns>
	auto E_cparhdr(const unsigned short& cparhdr)->void;

	/// <summary>
	/// Get Minimum extra paragraphs needed.
	/// </summary>
	/// <returns>Minimum extra paragraphs needed.</returns>
	auto E_minalloc() const ->unsigned short;

	/// <summary>
	/// Set Minimum extra paragraphs needed.
	/// </summary>
	/// <param name="minalloc">Minimum extra paragraphs needed</param>
	/// <returns></returns>
	auto E_minalloc(const unsigned short& minalloc)->void;

	/// <summary>
	/// Get Maximum extra paragraphs needed.
	/// </summary>
	/// <returns>Maximum extra paragraphs needed.</returns>
	auto E_maxalloc() const ->unsigned short;

	/// <summary>
	/// Set Maximum extra paragraphs needed.
	/// </summary>
	/// <param name="maxalloc">Maximum extra paragraphs needed.</param>
	/// <returns></returns>
	auto E_maxalloc(const unsigned short& maxalloc)->void;

	/// <summary>
	/// Get Initial (relative) SS value.
	/// </summary>
	/// <returns>Initial (relative) SS value.</returns>
	auto E_ss() const ->unsigned short;

	/// <summary>
	/// Set Initial (relative) SS value.
	/// </summary>
	/// <param name="ss">Initial (relative) SS value.</param>
	/// <returns></returns>
	auto E_ss(const unsigned short& ss)->void;

	/// <summary>
	/// Get Initial SP value.
	/// </summary>
	/// <returns>Initial SP value.</returns>
	auto E_sp() const ->unsigned short;

	/// <summary>
	/// Set Initial SP value.
	/// </summary>
	/// <param name="sp">Initial SP value.</param>
	/// <returns></returns>
	auto E_sp(const unsigned short& sp)->void;

	/// <summary>
	/// Get Checksum.
	/// </summary>
	/// <returns>Checksum as unsigned short</returns>
	auto E_csum() const ->unsigned short;

	/// <summary>
	/// Set Checksum.
	/// </summary>
	/// <param name="csum">Checksum.</param>
	/// <returns></returns>
	auto E_csum(const unsigned short& csum)->void;

	/// <summary>
	/// Get Initial IP value.
	/// </summary>
	/// <returns>Initial IP value as unsigned short</returns>
	auto E_ip() const ->unsigned short;

	/// <summary>
	/// Set Initial IP value.
	/// </summary>
	/// <param name="csum">Initial IP value</param>
	/// <returns></returns>
	auto E_ip(const unsigned short& csum)->void;

	/// <summary>
	/// Get Initial (relative) CS value.
	/// </summary>
	/// <returns>Initial (relative) CS value</returns>
	auto E_cs() const ->unsigned short;

	/// <summary>
	/// Set Initial (relative) CS value.
	/// </summary>
	/// <param name="cs">Initial (relative) CS value.</param>
	/// <returns></returns>
	auto E_cs(const unsigned short& cs)->void;

	/// <summary>
	/// Get Raw address of the relocation table.
	/// </summary>
	/// <returns>Raw address of the relocation table.</returns>
	auto E_lfarlc() const ->unsigned short;

	/// <summary>
	/// Set Raw address of the relocation table.
	/// </summary>
	/// <param name="lfarlc">Raw address of the relocation table.</param>
	/// <returns></returns>
	auto E_lfarlc(const unsigned short& lfarlc)->void;

	/// <summary>
	/// Get Overlay number.
	/// </summary>
	/// <returns>Overlay number.</returns>
	auto E_ovno() const ->unsigned short;

	/// <summary>
	/// Set Overlay number.
	/// </summary>
	/// <param name="evno">Overlay number.</param>
	/// <returns></returns>
	auto E_ovno(const unsigned short& evno)->void;

	/// <summary>
	/// Reserved.
	/// </summary>
	/// <returns>unknown</returns>
	auto E_res() const->std::vector<unsigned short>;

	/// <summary>
	/// Reserved.
	/// </summary>
	/// <param name="evno">Unknown</param>
	/// <returns></returns>
	auto E_res(const std::vector<unsigned short>& evno)->void;

	/// <summary>
	/// Get OEM identifier.
	/// </summary>
	/// <returns>OEM identifier.</returns>
	auto E_oemid() const ->unsigned short;

	/// <summary>
	/// Set OEM identifier.
	/// </summary>
	/// <param name="oemid">OEM identifier.</param>
	/// <returns></returns>
	auto E_oemid(const unsigned short& oemid)->void;

	/// <summary>
	/// Get OEM information.
	/// </summary>
	/// <returns>OEM information.</returns>
	auto E_oeminfo() const ->unsigned short;

	/// <summary>
	/// Set OEM information.
	/// </summary>
	/// <param name="oeminfo">OEM information.</param>
	/// <returns></returns>
	auto E_oeminfo(const unsigned short& oeminfo)->void;

	/// <summary>
	/// Reserved.
	/// </summary>
	/// <returns>Unknown</returns>
	auto E_res2() const->std::vector<unsigned short>;

	/// <summary>
	/// Reserved.
	/// </summary>
	/// <param name="res">Unknown</param>
	/// <returns></returns>
	auto E_res2(const std::vector<unsigned short>& res)->void;

	/// <summary>
	/// Get Raw address of the NT header.
	/// </summary>
	/// <returns>Raw address of the NT header.</returns>
	auto E_lfanew() const ->unsigned int;

	/// <summary>
	/// Set Raw address of the NT header.
	/// </summary>
	/// <param name="elfanew">Raw address of the NT header.</param>
	/// <returns></returns>
	auto E_lfanew(const unsigned int& elfanew)->void;

private:
	ImageDosHeader() = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;

	friend class PE;
};

