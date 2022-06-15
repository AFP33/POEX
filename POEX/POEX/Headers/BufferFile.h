#pragma once

#include "IRaw.h"

/// <summary>
/// Raw data parser based on IRaw abstract object
/// </summary>
class BufferFile : IRaw
{
public:
	/// <summary>
	/// Constructor as bytes array
	/// </summary>
	/// <param name="data">data as bytes array</param>
	explicit BufferFile(const std::vector<byte>& data);

	/// <summary>
	/// Constructor as current object
	/// </summary>
	/// <param name="bFile"></param>
	explicit BufferFile(const BufferFile& bFile);

	/// Destructor
	~BufferFile() = default;

	auto operator=(const BufferFile& bFile)->void;

	/// <summary>
	/// Get subset array from data
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <param name="length">Length of the subset</param>
	/// <returns>Array of bytes</returns>
	auto SubArray(const long& offset, const int& length)->std::vector<byte> override;

	/// <summary>
	/// Read single byte
	/// </summary>
	/// <param name="offset">Location of byte</param>
	/// <returns>Byte data</returns>
	auto ReadByte(const long& offset)->byte override;

	/// <summary>
	/// read unsigned short (just 2 bytes)
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>Unsigned short data</returns>
	auto ReadUnsignedShort(const long& offset)-> unsigned short override;

	/// <summary>
	/// Read unsigned int (just 4 bytes)
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>Unsigned int data</returns>
	auto ReadUnsignedInt(const long& offset)-> unsigned int override;

	/// <summary>
	/// read unsigned long (just 4 bytes)
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>Unsigned long data</returns>
	auto ReadUnsignedLong(const long& offset)-> unsigned long override;

	/// <summary>
	/// Write single byte in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="value">Value to writing</param>
	/// <returns></returns>
	auto WriteByte(const long& offset, const byte& value)-> void override;

	/// <summary>
	/// Write array of bytes in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Array of byte that want to write</param>
	/// <returns></returns>
	auto WriteBytes(const long& offset, const std::vector<byte>& bytes)-> void override;

	/// <summary>
	/// Write unsigned short (2 byte value) in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Data that want to write</param>
	/// <returns></returns>
	auto WriteUnsignedShort(const long& offset, const unsigned short& value)-> void override;

	/// <summary>
	/// Write unsigned long (4 byte value) in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Data that want to write</param>
	/// <returns></returns>
	auto WriteUnsignedLong(const long& offset, const unsigned long& value)-> void override;

	/// <summary>
	/// Write unsigned int (4 byte value) in specified offset
	/// </summary>
	/// <param name="offset">Location of start writing</param>
	/// <param name="bytes">Data that want to write</param>
	/// <returns></returns>
	auto WriteUnsignedInt(const long& offset, const unsigned int& value)-> void override;

	/// <summary>
	/// Read unicode string from data based on specified offset
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>unicode string as wstring</returns>
	auto ReadUnicodeString(const long& offset)->std::wstring override;

	/// <summary>
	/// Read unicode string from data based on specified offset and length
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <param name="length">Length of string</param>
	/// <returns>Unicode string as wstring</returns>
	auto ReadUnicodeString(const long& offset, const long& length)->std::wstring override;

	/// <summary>
	/// Read ASCII string from data based on specified offset
	/// </summary>
	/// <param name="offset">Location of start reading</param>
	/// <returns>ASCII string as std::string</returns>
	auto ReadAsciiString(const long& offset)->std::string override;

	/// <summary>
	/// Retrieve data
	/// </summary>
	/// <returns>Array of data as vector</returns>
	auto Data()->std::vector<byte> override;

	/// <summary>
	/// Size of data
	/// </summary>
	/// <returns>Data length</returns>
	auto Length()->size_t override;

	/// <summary>
	/// Remove part of data
	/// </summary>
	/// <param name="offset">Location for start removing</param>
	/// <param name="length">The length of data want to remove</param>
	/// <returns></returns>
	auto RemoveRange(const long& offset, const unsigned long length)-> void override;

	template <typename T>
	static std::vector<byte> ToBytesArray(T input)
	{
		std::vector<byte> result;
		byte* bytePointer = reinterpret_cast<byte*>(&input);
		result.insert(result.end(), bytePointer, bytePointer + sizeof(input));
		return result;
	}

	template <typename T>
	static T BytesArrayTo(std::vector<byte> input, int offset = 0)
	{
		if (input.size() < sizeof(T))
			THROW_EXCEPTION("[ERROR] Conversion fail.");
		T* t = reinterpret_cast<T*>(input.data() + offset);
		return (*t);
	}

private:
	BufferFile() = default;
	BufferFile(BufferFile&&) = default;

	std::vector<byte> data;

	auto GetSubVector(const std::vector<byte>& vec, const long& start, const long& end)->std::vector<byte>;
};

