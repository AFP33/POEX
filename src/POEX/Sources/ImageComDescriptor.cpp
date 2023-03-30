#include "../Headers/ImageComDescriptor.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageComDescriptor::ImageComDescriptor(const std::shared_ptr<BufferFile>& bFile, const long& offset) :
	bFile(bFile), offset(offset)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
	this->_exportAddressTableJumps = NULL;
	this->_strongSignatureNames = NULL;
	this->_managedNativeHeader = NULL;
	this->_codeManagerTable = NULL;
	this->_vTableFixups = NULL;
	this->_resources = NULL;
	this->_metaData = NULL;
}

auto ImageComDescriptor::ResolveComFlags(const ComFlagsType& comFlags) -> std::vector<std::string>
{
	try
	{
		std::vector<std::string> flags;

		if (comFlags & ComFlagsType::BitRequired32)
			flags.push_back("32Bit Required");
		if (comFlags & ComFlagsType::IlLibrary)
			flags.push_back("IL Library");
		if (comFlags & ComFlagsType::IlOnly)
			flags.push_back("IL Only");
		if (comFlags & ComFlagsType::NativeEntrypoint)
			flags.push_back("Native Entrypoint");
		if (comFlags & ComFlagsType::StrongNameSigned)
			flags.push_back("Strong Name Signed");
		if (comFlags & ComFlagsType::TrackDebugData)
			flags.push_back("Track Debug Data");

		return flags;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::Cb() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0000);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::Cb(const unsigned int& size) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0000, size);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::MajorRuntimeVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0004);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::MajorRuntimeVersion(const unsigned short& version) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0004, version);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::MinorRuntimeVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(this->offset + 0x0006);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::MinorRuntimeVersion(const unsigned short& version) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(this->offset + 0x0006, version);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::MetaData() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_metaData != NULL ?
			this->_metaData :
			this->_metaData = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0008);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::Flags() const -> ComFlagsType
{
	try
	{
		return static_cast<ComFlagsType>(this->bFile->ReadUnsignedInt(this->offset + 0x0010));
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::FlagsResolved() const -> std::vector<std::string>
{
	try
	{
		return ResolveComFlags(Flags());
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::EntryPointToken() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(this->offset + 0x0014);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::EntryPointToken(const unsigned int& entryPoint) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(this->offset + 0x0014, entryPoint);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::EntryPointRva() const -> unsigned int
{
	try
	{
		return EntryPointToken();
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::EntryPointRva(const unsigned int& entryPoint) -> void
{
	try
	{
		EntryPointToken(entryPoint);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::Resources() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_resources != NULL ? 
			this->_resources : 
			this->_resources = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0018);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::StrongNameSignature() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_strongSignatureNames != NULL ?
			this->_strongSignatureNames :
			this->_strongSignatureNames = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0020);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::CodeManagerTable() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_codeManagerTable != NULL ?
			this->_codeManagerTable :
			this->_codeManagerTable = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0028);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::VTableFixups() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_vTableFixups != NULL ?
			this->_vTableFixups :
			this->_vTableFixups = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0030);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::ExportAddressTableJumps() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_exportAddressTableJumps != NULL ?
			this->_exportAddressTableJumps :
			this->_exportAddressTableJumps = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0038);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageComDescriptor::ManagedNativeHeader() -> std::shared_ptr<ImageDataDirectory>
{
	try
	{
		return this->_managedNativeHeader != NULL ?
			this->_managedNativeHeader :
			this->_managedNativeHeader = std::make_shared<ImageDataDirectory>(this->bFile, this->offset + 0x0040);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
