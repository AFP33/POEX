#pragma once

#include "BufferFile.h"
#include "ImageDataDirectory.h"

/// <summary>
/// ImageComDescriptor Flags
/// </summary>
enum ComFlagsType : unsigned int
{
    /// <summary>
    /// Intermediate language only flag.
    /// </summary>
    IlOnly = 0x00000001,

    /// <summary>
    /// 32 bit required flag.
    /// </summary>
    BitRequired32 = 0x00000002,

    /// <summary>
    /// Intermediate language library flag.
    /// </summary>
    IlLibrary = 0x00000004,

    /// <summary>
    /// Strong named signed flag.
    /// </summary>
    StrongNameSigned = 0x00000008,

    /// <summary>
    /// Native entry point flag.
    /// </summary>
    NativeEntrypoint = 0x00000010,

    /// <summary>
    /// Track debug data flag.
    /// </summary>
    TrackDebugData = 0x00010000
};

class ImageComDescriptor
{
public:
	/// <summary>
	/// Create a new instance of an COM+ 2 (CLI) header.
	/// </summary>
	/// <param name="bFile">A PE file.</param>
	/// <param name="offset">Offset of the structure in the buffer.</param>
	ImageComDescriptor(const std::shared_ptr<BufferFile>& bFile, const long& offset);
	~ImageComDescriptor() = default;

    /// <summary>
    /// Resolve flags from the ImageCor20Header COM+ 2 (CLI) header to their string representation.
    /// </summary>
    /// <param name="comFlags">Flags from ImageCor20Header.</param>
    /// <returns>List with resolved flag names.</returns>
    static auto ResolveComFlags(const ComFlagsType& comFlags) -> std::vector<std::string>;

	/// <summary>
	/// Size of the structure.
	/// </summary>
	/// <returns>The structure Length</returns>
	auto Cb() const -> unsigned int;

	/// <summary>
	/// Size of the structure.
	/// </summary>
	/// <param name="size">The structure Length</param>
	/// <returns></returns>
	auto Cb(const unsigned int& size) -> void;

	/// <summary>
	/// Major runtime version of the CRL.
	/// </summary>
	/// <returns>Major version</returns>
	auto MajorRuntimeVersion() const -> unsigned short;

	/// <summary>
	/// Major runtime version of the CRL.
	/// </summary>
	/// <param name="version">Major version</param>
	/// <returns></returns>
	auto MajorRuntimeVersion(const unsigned short& version) -> void;

	/// <summary>
	/// Minor runtime version of the CRL.
	/// </summary>
	/// <returns>Minor version</returns>
	auto MinorRuntimeVersion() const -> unsigned short;

	/// <summary>
	/// Minor runtime version of the CRL.
	/// </summary>
	/// <param name="version">Minor version</param>
	/// <returns></returns>
	auto MinorRuntimeVersion(const unsigned short& version) -> void;

    /// <summary>
    /// Meta data directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto MetaData() -> std::shared_ptr<ImageDataDirectory>;

    /// <summary>
    /// COM image flags.
    /// </summary>
    /// <returns>ComFlagsType enum</returns>
    auto Flags() const -> ComFlagsType;

    /// <summary>
    /// Readable list of COM flags.
    /// </summary>
    /// <returns>List of flags string</returns>
    auto FlagsResolved() const -> std::vector<std::string>;

    /// <summary>
    /// Represents the managed entry point if NativeEntrypoint is not set. Union with EntryPointRVA.
    /// </summary>
    /// <returns>Entry point token</returns>
    auto EntryPointToken() const -> unsigned int;

    /// <summary>
    /// Represents the managed entry point if NativeEntrypoint is not set. Union with EntryPointRVA.
    /// </summary>
    /// <param name="entryPoint">Entry point token</param>
    /// <returns></returns>
    auto EntryPointToken(const unsigned int& entryPoint) -> void;

    /// <summary>
    /// Represents an RVA to an native entry point if the NativeEntrypoint is set. Union with EntryPointToken.
    /// </summary>
    /// <returns>Entry point rva</returns>
    auto EntryPointRva() const -> unsigned int;

    /// <summary>
    /// Represents an RVA to an native entry point if the NativeEntrypoint is set. Union with EntryPointToken.
    /// </summary>
    /// <param name="entryPoint">Entry point rva</param>
    /// <returns></returns>
    auto EntryPointRva(const unsigned int& entryPoint) -> void;

    /// <summary>
    /// Resource data directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto Resources() -> std::shared_ptr<ImageDataDirectory>;

    /// <summary>
    /// Strong names signature directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto StrongNameSignature() -> std::shared_ptr<ImageDataDirectory>;

    /// <summary>
    /// Code manager table directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto CodeManagerTable() -> std::shared_ptr<ImageDataDirectory>;

    /// <summary>
    /// Virtual table fix up directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto VTableFixups() -> std::shared_ptr<ImageDataDirectory>;

    /// <summary>
    /// Export address table jump directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto ExportAddressTableJumps() -> std::shared_ptr<ImageDataDirectory>;

    /// <summary>
    /// Managed native header directory.
    /// </summary>
    /// <returns>Pointer of ImageDataDirectory object</returns>
    auto ManagedNativeHeader() -> std::shared_ptr<ImageDataDirectory>;

private:
	ImageComDescriptor() = default;
	ImageComDescriptor(const ImageComDescriptor&) = default;

	// variables
	std::shared_ptr<BufferFile> bFile;
	long offset;

    std::shared_ptr<ImageDataDirectory> _metaData;
    std::shared_ptr<ImageDataDirectory> _resources;
    std::shared_ptr<ImageDataDirectory> _strongSignatureNames;
    std::shared_ptr<ImageDataDirectory> _codeManagerTable;
    std::shared_ptr<ImageDataDirectory> _vTableFixups;
    std::shared_ptr<ImageDataDirectory> _exportAddressTableJumps;
    std::shared_ptr<ImageDataDirectory> _managedNativeHeader;
};