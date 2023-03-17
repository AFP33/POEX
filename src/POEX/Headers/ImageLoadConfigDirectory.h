#pragma once

#include "BufferFile.h"

/// <summary>
/// The ImageLoadConfigDirectory hold information
/// important to load the PE file correctly.
/// </summary>
class ImageLoadConfigDirectory
{
public:

	/// <summary>
	/// Create a new ImageLoadConfigDirectory object.
	/// </summary>
    /// <param name="peFile">A PE file.</param>
    /// <param name="offset">Offset of the structure in the buffer.</param>
    /// <param name="is64Bit">Flag if the PE file is 64 Bit.</param>
	ImageLoadConfigDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, const bool& is64Bit);
	~ImageLoadConfigDirectory() = default;

	/// <summary>
	/// SIze of the ImageLoadConfigDirectory structure.
	/// </summary>
	/// <returns>size</returns>
	auto Size() const -> unsigned int;

	/// <summary>
	/// SIze of the ImageLoadConfigDirectory structure.
	/// </summary>
	/// <param name="size">size</param>
	/// <returns></returns>
	auto Size(const unsigned int& size) -> void;

	/// <summary>
	/// Time and date stamp. Shows seconds elapsed since 00:00:00, January 1, 1970 in UCT.
	/// </summary>
	/// <returns>Time</returns>
	auto TimeDateStamp() const -> unsigned int;

	/// <summary>
	/// Time and date stamp. Shows seconds elapsed since 00:00:00, January 1, 1970 in UCT.
	/// </summary>
	/// <param name="time">time</param>
	/// <returns></returns>
	auto TimeDateStamp(const unsigned int& time) -> void;

	/// <summary>
	/// Major version number.
	/// </summary>
	/// <returns></returns>
	auto MajorVesion() const -> unsigned short;

	/// <summary>
	/// Major version number.
	/// </summary>
	/// <param name="majorVersion">Major version</param>
	/// <returns></returns>
	auto MajorVesion(const unsigned short& majorVersion) -> void;

	/// <summary>
	/// Minor version number.
	/// </summary>
	/// <returns></returns>
	auto MinorVersion() const -> unsigned short;

	/// <summary>
	/// Minor version number.
	/// </summary>
	/// <param name="minorVersion">Minor version</param>
	/// <returns></returns>
	auto MinorVersion(const unsigned short& minorVersion) -> void;

	/// <summary>
	/// GLobal flags to control system behavior.
	/// </summary>
	/// <returns></returns>
	auto GlobalFlagsClear() const -> unsigned int;

	/// <summary>
	/// GLobal flags to control system behavior.
	/// </summary>
	/// <param name="globalFlagsClear">GLobal flags</param>
	/// <returns></returns>
	auto GlobalFlagsClear(const unsigned int& globalFlagsClear) -> void;

	/// <summary>
	/// Global flags to control system behavior.
	/// </summary>
	/// <returns></returns>
	auto GlobalFlagsSet() const -> unsigned int;

	/// <summary>
	/// Global flags to control system behavior.
	/// </summary>
	/// <param name="globalFlagsClear">GLobal flags</param>
	/// <returns></returns>
	auto GlobalFlagsSet(const unsigned int& globalFlagsSet) -> void;

	/// <summary>
	/// Default time-out value for critical sections.
	/// </summary>
	/// <returns></returns>
	auto CriticalSectionDefaultTimeout() const -> unsigned int;

	/// <summary>
	/// Default time-out value for critical sections.
	/// </summary>
	/// <param name="criticalSectionDefaultTimeout">Default time-out</param>
	/// <returns></returns>
	auto CriticalSectionDefaultTimeout(const unsigned int& criticalSectionDefaultTimeout) -> void;

	/// <summary>
	/// The size of the minimum block that has to be freed before it's freed in bytes.
	/// </summary>
	/// <returns></returns>
	auto DeCommitFreeBlockThreshold() const -> unsigned long;

	/// <summary>
	/// The size of the minimum block that has to be freed before it's freed in bytes.
	/// </summary>
	/// <param name="deCommitFreeBlockThreshold">The size of the minimum block</param>
	/// <returns></returns>
	auto DeCommitFreeBlockThreshold(const unsigned long& deCommitFreeBlockThreshold) -> void;

	/// <summary>
	/// SIze of the minimum total heap memory that has to be freed before it is freed in bytes.
	/// </summary>
	/// <returns>SIze of the minimum total heap memory</returns>
	auto DeCommitTotalFreeThreshold() const -> unsigned long;

	/// <summary>
	/// SIze of the minimum total heap memory that has to be freed before it is freed in bytes.
	/// </summary>
	/// <param name="deCommitTotalFreeThreshold">SIze of the minimum total heap memory</param>
	/// <returns></returns>
	auto DeCommitTotalFreeThreshold(const unsigned long& deCommitTotalFreeThreshold) -> void;

	/// <summary>
	/// Virtual Address of a list with addresses where the LOCK prefix is used.
	/// Will be replaced by NOP instructions on single-processor systems. Only available on x86.
	/// </summary>
	/// <returns>Virtual Address of a list</returns>
	auto LockPrefixTable() const -> unsigned long;

	/// <summary>
	/// Virtual Address of a list with addresses where the LOCK prefix is used.
	/// Will be replaced by NOP instructions on single-processor systems. Only available on x86.
	/// </summary>
	/// <param name="lockPrefixTable">Virtual Address of a list</param>
	/// <returns></returns>
	auto LockPrefixTable(const unsigned long& lockPrefixTable) -> void;

	/// <summary>
	/// The maximum allocation size in bytes. Only used for debugging purposes.
	/// </summary>
	/// <returns>The maximum allocation size</returns>
	auto MaximumAllocationSize() const -> unsigned long;

	/// <summary>
	/// The maximum allocation size in bytes. Only used for debugging purposes.
	/// </summary>
	/// <param name="maximumAllocationSize">The maximum allocation size</param>
	/// <returns></returns>
	auto MaximumAllocationSize(const unsigned long& maximumAllocationSize) -> void;

	/// <summary>
	/// The maximum block size that can be allocated from heap segments in bytes.
	/// </summary>
	/// <returns>The maximum block size</returns>
	auto VirtualMemoryThreshold() const -> unsigned long;

	/// <summary>
	/// The maximum block size that can be allocated from heap segments in bytes.
	/// </summary>
	/// <param name="virtualMemoryThreshold">The maximum block size</param>
	/// <returns></returns>
	auto VirtualMemoryThreshold(const unsigned long& virtualMemoryThreshold) -> void;

	/// <summary>
	/// The processor affinity mask defines on which CPU the executable should run.
	/// </summary>
	/// <returns>The processor affinity mask</returns>
	auto ProcessAffinityMask() const -> unsigned long;

	/// <summary>
	/// The processor affinity mask defines on which CPU the executable should run.
	/// </summary>
	/// <param name="processAffinityMask">The processor affinity mask</param>
	/// <returns></returns>
	auto ProcessAffinityMask(const unsigned long& processAffinityMask) -> void;

	/// <summary>
	/// The process heap flags.
	/// </summary>
	/// <returns>The process heap flags.</returns>
	auto ProcessHeapFlags() const -> unsigned int;

	/// <summary>
	/// The process heap flags.
	/// </summary>
	/// <param name="processHeapFlags">The process heap flags</param>
	/// <returns></returns>
	auto ProcessHeapFlags(const unsigned int& processHeapFlags) -> void;

	/// <summary>
	/// Service pack version.
	/// </summary>
	/// <returns>Service pack version.</returns>
	auto CSDVersion() const -> unsigned short;

	/// <summary>
	/// Service pack version.
	/// </summary>
	/// <param name="cSDVersion">Service pack version.</param>
	/// <returns></returns>
	auto CSDVersion(const unsigned short& cSDVersion) -> void;

	/// <summary>
	/// Reserved for use by the operating system.
	/// </summary>
	/// <returns></returns>
	auto Reserved1() const -> unsigned short;

	/// <summary>
	/// Reserved for use by the operating system.
	/// </summary>
	/// <param name="reserved1">value</param>
	/// <returns></returns>
	auto Reserved1(const unsigned short& reserved1) -> void;

	/// <summary>
	/// Reserved for use by the operating system.
	/// </summary>
	/// <returns></returns>
	auto EditList() const -> unsigned long;

	/// <summary>
	/// Reserved for use by the operating system.
	/// </summary>
	/// <param name="editList"></param>
	/// <returns></returns>
	auto EditList(const unsigned long& editList) -> void;

	/// <summary>
	/// Pointer to a cookie used by Visual C++ or GS implementation.
	/// </summary>
	/// <returns>coockie</returns>
	auto SecurityCoockie() const -> unsigned long;

	/// <summary>
	/// Pointer to a cookie used by Visual C++ or GS implementation.
	/// </summary>
	/// <param name="securityCoockie">coockie</param>
	/// <returns></returns>
	auto SecurityCoockie(const unsigned long& securityCoockie) -> void;

	/// <summary>
	/// Virtual Address of a sorted table of RVAs of each valid and unique handler in the image.
	/// Only available on x86.
	/// </summary>
	/// <returns>handler</returns>
	auto SEHandlerTable() const -> unsigned long;

	/// <summary>
	/// Virtual Address of a sorted table of RVAs of each valid and unique handler in the image.
	/// Only available on x86.
	/// </summary>
	/// <param name="sEHandlerTable">handler</param>
	/// <returns></returns>
	auto SEHandlerTable(const unsigned long& sEHandlerTable) -> void;

	/// <summary>
	/// Count of unique exception handlers in the table. Only available on x86.
	/// </summary>
	/// <returns>count</returns>
	auto SEHandlerCount() const -> unsigned long;

	/// <summary>
	/// Count of unique exception handlers in the table. Only available on x86.
	/// </summary>
	/// <param name="sEHandlerCount">count</param>
	/// <returns></returns>
	auto SEHandlerCount(const unsigned long& sEHandlerCount) -> void;

	/// <summary>
	/// Control flow guard (Win 8.1 and up) function pointer.
	/// </summary>
	/// <returns>Control flow guard</returns>
	auto GuardCFCheckFunctionPointer() const -> unsigned long;

	/// <summary>
	/// Control flow guard (Win 8.1 and up) function pointer.
	/// </summary>
	/// <param name="guardCFCheckFunctionPointer">Control flow guard</param>
	/// <returns></returns>
	auto GuardCFCheckFunctionPointer(const unsigned long& guardCFCheckFunctionPointer) -> void;

	/// <summary>
	/// Reserved
	/// </summary>
	/// <returns></returns>
	auto Reserved2() const -> unsigned long;

	/// <summary>
	/// Reserved
	/// </summary>
	/// <param name="reserved2"></param>
	/// <returns></returns>
	auto Reserved2(const unsigned long& reserved2) -> void;

	/// <summary>
	/// Pointer to the control flow guard function table. Only on Win 8.1 and up.
	/// </summary>
	/// <returns></returns>
	auto GuardCFFunctionTable() const -> unsigned long;

	/// <summary>
	/// Pointer to the control flow guard function table. Only on Win 8.1 and up.
	/// </summary>
	/// <param name="guardCFFunctionTable"></param>
	/// <returns></returns>
	auto GuardCFFunctionTable(const unsigned long& guardCFFunctionTable) -> void;

	/// <summary>
	/// Count of functions under control flow guard. Only on Win 8.1 and up.
	/// </summary>
	/// <returns>Count of functions</returns>
	auto GuardCFFunctionCount() const -> unsigned long;

	/// <summary>
	/// Count of functions under control flow guard. Only on Win 8.1 and up.
	/// </summary>
	/// <param name="guardCFFunctionCount">Count of functions</param>
	/// <returns></returns>
	auto GuardCFFunctionCount(const unsigned long& guardCFFunctionCount) -> void;

	/// <summary>
	/// Flags for the control flow guard. Only on Win 8.1 and up.
	/// </summary>
	/// <returns>the control flow guard flag</returns>
	auto GuardFlags() const -> unsigned long;

	/// <summary>
	/// Flags for the control flow guard. Only on Win 8.1 and up.
	/// </summary>
	/// <param name="guardFlags"> the control flow guard flag</param>
	/// <returns></returns>
	auto GuardFlags(const unsigned long& guardFlags) -> void;

private:
	ImageLoadConfigDirectory(const ImageLoadConfigDirectory&) = default;
	ImageLoadConfigDirectory() = default;

	std::shared_ptr<BufferFile> bFile;
	long offset;
	bool is64Bit;
};