#include "../Headers/BufferFile.h"

BufferFile::BufferFile(const std::vector<byte>& data) : data(data)
{
}

BufferFile::BufferFile(const BufferFile& bFile) : data(bFile.data)
{
}

auto BufferFile::operator=(const BufferFile& bFile) -> void
{
	this->data = bFile.data;
}

auto BufferFile::SubArray(const long& offset, const int& length) -> std::vector<byte>
{
	auto firstIt = data.begin() + offset;
	auto laseIt = data.begin() + offset + length;
	return std::vector<byte>(firstIt, laseIt);
}

auto BufferFile::ReadByte(const long& offset) -> byte
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	return this->data[offset];
}

auto BufferFile::ReadUnsignedShort(const long& offset) -> unsigned short
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	return BytesArrayTo<unsigned short>(this->data, offset);
}

auto BufferFile::ReadUnsignedInt(const long& offset) -> unsigned int
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	return BytesArrayTo<unsigned int>(this->data, offset);
}

auto BufferFile::ReadUnsignedLong(const long& offset) -> unsigned long
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	return BytesArrayTo<unsigned long>(this->data, offset);
}

auto BufferFile::WriteByte(const long& offset, const byte& value) -> void
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	this->data[offset] = value;
}

auto BufferFile::WriteBytes(const long& offset, const std::vector<byte>& bytes) -> void
{
	if (WRONG_LONG(offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
	if (EMPTY_VECTOR(bytes))
		THROW_OUT_OF_RANGE("[ERROR] data cann't be empty.");
	auto position = std::next(this->data.cbegin(), offset);
	this->data.erase(position, position + 8);
	position = std::next(this->data.cbegin(), offset);
	this->data.insert(position, bytes.begin(), bytes.end());
}

auto BufferFile::WriteUnsignedShort(const long& offset, const unsigned short& value) -> void
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	this->WriteByte(offset, (byte)value);
}

auto BufferFile::WriteUnsignedLong(const long& offset, const unsigned long& value) -> void
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	this->WriteByte(offset, (byte)value);
}

auto BufferFile::WriteUnsignedInt(const long& offset, const unsigned int& value) -> void
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	this->WriteByte(offset, (byte)value);
}

auto BufferFile::ReadUnicodeString(const long& offset) -> std::wstring
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	auto item = this->data[offset];
	return std::wstring((wchar_t*)item);
}

auto BufferFile::ReadUnicodeString(const long& offset, const long& length) -> std::wstring
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	if (WRONG_LONG(length))
		THROW_OUT_OF_RANGE("[ERROR] length value is wrong.");
	auto vec = GetSubVector(this->data, offset, offset + length);
	return std::wstring((wchar_t*)&vec[0], vec.size());
}

auto BufferFile::ReadAsciiString(const long& offset) -> std::string
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	std::vector<byte> str;
	auto pos = offset;
	while (this->data[pos] != 0x00)
	{
		str.push_back(this->data[pos]);
		pos++;
	}

	return std::string(str.begin(), str.end());
}

auto BufferFile::Data() -> std::vector<byte>
{
	return this->data;
}

auto BufferFile::Length() -> size_t
{
	return this->data.size();
}

auto BufferFile::RemoveRange(const long& offset, const unsigned long length) -> void
{
	if (WRONG_LONG(offset))
		THROW_OUT_OF_RANGE("[ERROR] offset value is wrong.");
	auto startPosition = std::next(this->data.cbegin(), offset);
	auto pos = offset + length;
	auto endPosition = std::next(this->data.cbegin(), pos);
	this->data.erase(startPosition, endPosition);
}

auto BufferFile::GetSubVector(const std::vector<byte>& vec, const long& startPosition, const long& endPosition) -> std::vector<byte>
{
	auto begin = vec.begin() + startPosition;
	auto end = vec.begin() + endPosition;
	return std::vector<byte>(begin, end);
}
