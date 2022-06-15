#pragma once

#include "Headers.h"
#include "Defines.h"

typedef unsigned char byte;

/// <summary>
/// Abstract object for implement Different parsers
/// </summary>
class IRaw
{
public:

	/// <summary>
	/// Read single byte
	/// </summary>
	/// <param name="offset">Location of byte</param>
	/// <returns>Byte data</returns>
	virtual auto ReadByte(const long& offset) -> byte = 0;

	/// <summary>
	/// Get subset array from data
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <param name="length">Length of the subset</param>
	/// <returns>Array of bytes</returns>
	virtual auto SubArray(const long& offset, const int& length)->std::vector<byte> = 0;

	/// <summary>
	/// read unsigned short (just 2 bytes)
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>Unsigned short data</returns>
	virtual auto ReadUnsignedShort(const long& offset) -> unsigned short = 0;

	/// <summary>
	/// Read unsigned int (just 4 bytes)
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>Unsigned int data</returns>
	virtual auto ReadUnsignedInt(const long& offset) -> unsigned int = 0;

	/// <summary>
	/// read unsigned long (just 4 bytes)
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>Unsigned long data</returns>
	virtual auto ReadUnsignedLong(const long& offset) -> unsigned long = 0;

	/// <summary>
	/// Write single byte in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="value">Value to writing</param>
	/// <returns></returns>
	virtual auto WriteByte(const long& offset, const byte& value) -> void = 0;

	/// <summary>
	/// Write array of bytes in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Array of byte that want to write</param>
	/// <returns></returns>
	virtual auto WriteBytes(const long& offset, const std::vector<byte>& bytes)->void = 0;

	/// <summary>
	/// Write unsigned short (2 byte value) in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Data that want to write</param>
	/// <returns></returns>
	virtual auto WriteUnsignedShort(const long& offset, const unsigned short& value) -> void = 0;

	/// <summary>
	/// Write unsigned long (4 byte value) in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Data that want to write</param>
	/// <returns></returns>
	virtual auto WriteUnsignedLong(const long& offset, const unsigned long& value) -> void = 0;

	/// <summary>
	/// Write unsigned int (4 byte value) in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Data that want to write</param>
	/// <returns></returns>
	virtual auto WriteUnsignedInt(const long& offset, const unsigned int& value) -> void = 0;

	/// <summary>
	/// Read unicode string from data based on specified offset
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>unicode string as wstring</returns>
	virtual auto ReadUnicodeString(const long& offset)->std::wstring = 0;

	/// <summary>
	/// Read unicode string from data based on specified offset and length
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <param name="length">Length of string</param>
	/// <returns>Unicode string as wstring</returns>
	virtual auto ReadUnicodeString(const long& offset, const long& length)->std::wstring = 0;

	/// <summary>
	/// Read ASCII string from data based on specified offset
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>ASCII string as std::string</returns>
	virtual auto ReadAsciiString(const long& offset)->std::string = 0;

	/// <summary>
	/// Retrieve data
	/// </summary>
	/// <returns>Array of data as vector</returns>
	virtual auto Data()->std::vector<byte> = 0;

	/// <summary>
	/// Size of data
	/// </summary>
	/// <returns>Data length</returns>
	virtual auto Length()->size_t = 0;

	/// <summary>
	/// Remove part of data
	/// </summary>
	/// <param name="offset">Location for start removing</param>
	/// <param name="length">The length of data want to remove</param>
	/// <returns></returns>
	virtual auto RemoveRange(const long& offset, const unsigned long length)->void = 0;
};

