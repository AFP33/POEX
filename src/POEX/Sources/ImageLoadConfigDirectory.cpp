#include "../Headers/ImageLoadConfigDirectory.h"

ImageLoadConfigDirectory::ImageLoadConfigDirectory(const std::shared_ptr<BufferFile>& bFile, 
	const long& offset, const bool& is64Bit) :
	bFile(bFile), offset(offset), is64Bit(is64Bit)
{
}

auto ImageLoadConfigDirectory::Size() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::Size(const unsigned int& size) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x0000, size);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::TimeDateStamp() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::TimeDateStamp(const unsigned int& time) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x0004, time);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::MajorVesion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::MajorVesion(const unsigned short& majorVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(offset + 0x0008, majorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::MinorVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x000A);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::MinorVersion(const unsigned short& minorVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(offset + 0x000A, minorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GlobalFlagsClear() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x000C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GlobalFlagsClear(const unsigned int& globalFlagsClear) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x000C, globalFlagsClear);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GlobalFlagsSet() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x0010);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GlobalFlagsSet(const unsigned int& globalFlagsSet) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x0010, globalFlagsSet);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::CriticalSectionDefaultTimeout() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x0014);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::CriticalSectionDefaultTimeout(const unsigned int& criticalSectionDefaultTimeout) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x0014, criticalSectionDefaultTimeout);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::DeCommitFreeBlockThreshold() const -> unsigned long
{
	try
	{
		return is64Bit ? 
			this->bFile->ReadUnsignedLong(offset + 0x0018) : 
			this->bFile->ReadUnsignedInt(offset + 0x0018);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::DeCommitFreeBlockThreshold(const unsigned long& deCommitFreeBlockThreshold) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0018, deCommitFreeBlockThreshold);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0018, (unsigned int)deCommitFreeBlockThreshold);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::DeCommitTotalFreeThreshold() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0020) :
			this->bFile->ReadUnsignedInt(offset + 0x001C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::DeCommitTotalFreeThreshold(const unsigned long& deCommitTotalFreeThreshold) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0020, deCommitTotalFreeThreshold);
		else
			this->bFile->WriteUnsignedInt(offset + 0x001C, (unsigned int)deCommitTotalFreeThreshold);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::LockPrefixTable() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0028) :
			this->bFile->ReadUnsignedInt(offset + 0x0020);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::LockPrefixTable(const unsigned long& lockPrefixTable) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0028, lockPrefixTable);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0020, (unsigned int)lockPrefixTable);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::MaximumAllocationSize() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0030) :
			this->bFile->ReadUnsignedInt(offset + 0x0024);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::MaximumAllocationSize(const unsigned long& maximumAllocationSize) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0030, maximumAllocationSize);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0024, (unsigned int)maximumAllocationSize);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::VirtualMemoryThreshold() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0038) :
			this->bFile->ReadUnsignedInt(offset + 0x0028);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::VirtualMemoryThreshold(const unsigned long& virtualMemoryThreshold) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0038, virtualMemoryThreshold);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0028, (unsigned int)virtualMemoryThreshold);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::ProcessAffinityMask() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0040) :
			this->bFile->ReadUnsignedInt(offset + 0x0030);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::ProcessAffinityMask(const unsigned long& processAffinityMask) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0040, processAffinityMask);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0030, (unsigned int)processAffinityMask);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::ProcessHeapFlags() const -> unsigned int
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedInt(offset + 0x0048) :
			this->bFile->ReadUnsignedInt(offset + 0x002C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::ProcessHeapFlags(const unsigned int& processHeapFlags) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedInt(offset + 0x0048, processHeapFlags);
		else
			this->bFile->WriteUnsignedInt(offset + 0x002C, processHeapFlags);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::CSDVersion() const -> unsigned short
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedShort(offset + 0x004C) :
			this->bFile->ReadUnsignedShort(offset + 0x0034);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::CSDVersion(const unsigned short& cSDVersion) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedShort(offset + 0x004C, cSDVersion);
		else
			this->bFile->WriteUnsignedShort(offset + 0x0034, cSDVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::Reserved1() const -> unsigned short
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedShort(offset + 0x004E) :
			this->bFile->ReadUnsignedShort(offset + 0x0036);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::Reserved1(const unsigned short& reserved1) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedShort(offset + 0x004E, reserved1);
		else
			this->bFile->WriteUnsignedShort(offset + 0x0036, reserved1);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::EditList() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0050) :
			this->bFile->ReadUnsignedInt(offset + 0x0038);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::EditList(const unsigned long& editList) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0050, editList);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0038, (unsigned int)editList);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::SecurityCoockie() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0058) :
			this->bFile->ReadUnsignedInt(offset + 0x003C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::SecurityCoockie(const unsigned long& securityCoockie) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0058, securityCoockie);
		else
			this->bFile->WriteUnsignedInt(offset + 0x003C, (unsigned int)securityCoockie);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::SEHandlerTable() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0060) :
			this->bFile->ReadUnsignedInt(offset + 0x0040);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::SEHandlerTable(const unsigned long& sEHandlerTable) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0060, sEHandlerTable);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0040, (unsigned int)sEHandlerTable);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::SEHandlerCount() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0068) :
			this->bFile->ReadUnsignedInt(offset + 0x0044);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::SEHandlerCount(const unsigned long& sEHandlerCount) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0068, sEHandlerCount);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0044, (unsigned int)sEHandlerCount);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardCFCheckFunctionPointer() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0070) :
			this->bFile->ReadUnsignedInt(offset + 0x0048);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardCFCheckFunctionPointer(const unsigned long& guardCFCheckFunctionPointer) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0070, guardCFCheckFunctionPointer);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0048, (unsigned int)guardCFCheckFunctionPointer);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::Reserved2() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0078) :
			this->bFile->ReadUnsignedInt(offset + 0x004C);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::Reserved2(const unsigned long& reserved2) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0078, reserved2);
		else
			this->bFile->WriteUnsignedInt(offset + 0x004C, (unsigned int)reserved2);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardCFFunctionTable() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0080) :
			this->bFile->ReadUnsignedInt(offset + 0x0050);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardCFFunctionTable(const unsigned long& guardCFFunctionTable) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0080, guardCFFunctionTable);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0050, (unsigned int)guardCFFunctionTable);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardCFFunctionCount() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedLong(offset + 0x0088) :
			this->bFile->ReadUnsignedInt(offset + 0x0054);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardCFFunctionCount(const unsigned long& guardCFFunctionCount) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedLong(offset + 0x0088, guardCFFunctionCount);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0054, (unsigned int)guardCFFunctionCount);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardFlags() const -> unsigned long
{
	try
	{
		return is64Bit ?
			this->bFile->ReadUnsignedInt(offset + 0x0090) :
			this->bFile->ReadUnsignedInt(offset + 0x0058);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageLoadConfigDirectory::GuardFlags(const unsigned long& guardFlags) -> void
{
	try
	{
		if (is64Bit)
			this->bFile->WriteUnsignedInt(offset + 0x0090, guardFlags);
		else
			this->bFile->WriteUnsignedInt(offset + 0x0058, guardFlags);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
