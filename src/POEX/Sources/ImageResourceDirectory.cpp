#include "../Headers/ImageResourceDirectory.h"

/**
* Portable Executable (POEX) Project
* Developed by AFP33, 2023
* Url: https://github.com/AFP33/POEX
*/

ImageResourceDirectory::ImageResourceDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const long& resourceDirectoryOffset, const long& resourceDirectoryLength) :
	bFile(bFile), offset(offset), resourceDirectoryOffset(resourceDirectoryOffset), 
	resourceDirectoryLength(resourceDirectoryLength)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

ImageResourceDirectory::ImageResourceDirectory(const std::shared_ptr<BufferFile>& bFile, const long& offset, 
	const std::shared_ptr<ImageResourceDirectoryEntry>& parent, const long& resourceDirectoryOffset, 
	const long& resourceDirectoryLength) :
	bFile(bFile), offset(offset), parent(parent), resourceDirectoryOffset(resourceDirectoryOffset),
	resourceDirectoryLength(resourceDirectoryLength)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageResourceDirectory::ImageResourceDirectoryEntries() -> std::vector<std::shared_ptr<ImageResourceDirectoryEntry>>
{
	try
	{
		// Check if the number of entries is bigger than the resource directory and thus cannot be parsed correctly. 10 byte is the minimal size of an entry.
		if ((NumberOfIdEntries() + NumberOfNameEntries()) * 10 >= this->resourceDirectoryLength)
			return std::vector<std::shared_ptr<ImageResourceDirectoryEntry>>();

		auto DirectoryEntries = ParseDirectoryEntries();
		if (DirectoryEntries.size() == 0)
			return std::vector<std::shared_ptr<ImageResourceDirectoryEntry>>();

		// Parse the second stage (type)
		for (auto de : DirectoryEntries)
		{
			// This check only applies to the second level.
			if (de->IsIdEntry() && de->NameResolve() == "unknown")
				continue;

			auto b = std::make_shared<ImageResourceDirectory>(bFile,
				offset + de->OffsetToDirectory(), de, offset, resourceDirectoryLength);
			de->ResourceDirectory(b);

			auto sndLevel = de->ResourceDirectory()->ImageResourceDirectoryEntries();
			if (sndLevel.size() == 0)
				continue;

			for (auto de2 : sndLevel)
			{
				auto a = std::make_shared<ImageResourceDirectory>(bFile,
					offset + de2->OffsetToDirectory(), de2, offset, resourceDirectoryLength);
				de2->ResourceDirectory(a);

				auto thrdLevel = de2->ResourceDirectory()->ImageResourceDirectoryEntries();
				if (thrdLevel.size() == 0)
					continue;

				for (auto de3 : thrdLevel)
				{
					std::shared_ptr<ImageResourceDirectory> c(new ImageResourceDirectory(bFile,
						offset + de3->OffsetToDirectory(), de3, offset, resourceDirectoryLength));
					de3->ResourceDirectory(c);
				}
			}
		}
		return DirectoryEntries;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::ResourceDirectory() -> std::shared_ptr<ImageResourceDirectory>
{
	return this->resourceDirectory;
}

auto ImageResourceDirectoryEntry::ResourceDirectory(const std::shared_ptr<ImageResourceDirectory>& resourceDir) -> void
{
	this->resourceDirectory = resourceDir;
}

auto ImageResourceDirectory::Characteristics() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::Characteristics(const unsigned int& characteristics) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset, characteristics);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::TimeDateStamp() const -> unsigned int
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

auto ImageResourceDirectory::TimeDateStamp(const unsigned int& time) -> void
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

auto ImageResourceDirectory::MajorVersion() const -> unsigned short
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

auto ImageResourceDirectory::MajorVersion(const unsigned short& majorVersion) -> void
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

auto ImageResourceDirectory::MinorVersion() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x000a);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::MinorVersion(const unsigned short& minorVersion) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(offset + 0x000a, minorVersion);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::NumberOfNameEntries() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x000c);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::NumberOfNameEntries(const unsigned short& nameEntires) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(offset + 0x000c, nameEntires);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::NumberOfIdEntries() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset + 0x000e);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::NumberOfIdEntries(const unsigned short& idEntires) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(offset + 0x000e, idEntires);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::ParseDirectoryEntries() -> std::vector<std::shared_ptr<ImageResourceDirectoryEntry>>
{
	try
	{
		auto numEntries = NumberOfIdEntries() + NumberOfNameEntries();
		std::vector<std::shared_ptr<ImageResourceDirectoryEntry>> entries;
		for (size_t i = 0; i < numEntries; i++)
		{
			try
			{
				auto entry = std::make_shared<ImageResourceDirectoryEntry>(this->bFile, 
					std::make_shared<ImageResourceDirectory>(*this),
					(long)i * 8 + offset + 16, resourceDirectoryOffset);

				if (SanityCheckFailed(entry))
					break;

				entries.push_back(entry);

			}
			catch (const std::exception&)
			{
				break;
			}
		}
		return entries;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectory::SanityCheckFailed(const std::shared_ptr<ImageResourceDirectoryEntry>& entry) -> bool
{
	try
	{
		if (entry.get() == NULL)
			return true;

		if (entry->IsNamedEntry() && entry->NameResolve().empty())
			return true;

		if (entry->IsNamedEntry() && entry->NameResolve() == "unknown")
			return true;

		if (entry->OffsetToDirectory() > resourceDirectoryLength)
			return true;

		return false;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

ImageResourceDirectoryEntry::ImageResourceDirectoryEntry(const std::shared_ptr<BufferFile>& bFile, 
	const std::shared_ptr<ImageResourceDirectory>& parent, const long& offset, const long& resourceDirectoryOffset) :
	bFile(bFile), parent(parent), offset(offset), resourceDirectoryOffset(resourceDirectoryOffset)
{
	try
	{
		if (WRONG_LONG(this->offset))
			THROW_EXCEPTION("[ERROR] offset value is wrong.");

		if (IsIdEntry())
			NameResolved = ResolveResourceId(ID());
		else if (IsNamedEntry())
		{
			auto nameAddress = resourceDirectoryOffset + (Name() & 0x7FFFFFFF);
			auto unicodeName = std::make_unique<ImageResourceDirStringU>(this->bFile, nameAddress);
			NameResolved = std::string(unicodeName->NameString().begin(), unicodeName->NameString().end());
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::Parent() const -> std::shared_ptr<ImageResourceDirectory>
{
	try
	{
		return this->parent;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::NameResolve() const -> std::string
{
	return NameResolved;
}

auto ImageResourceDirectoryEntry::Name() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::Name(const unsigned int& name) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset, name);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::ID() const -> unsigned int
{
	try
	{
		return Name() & 0xFFFF;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::ID(const unsigned int& id) -> void
{
	try
	{
		Name(id & 0xFFFF);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::OffsetToData() const -> unsigned int
{
	try
	{
		return this->bFile->ReadUnsignedInt(offset + 0x4);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::OffsetToData(const unsigned int off) -> void
{
	try
	{
		this->bFile->WriteUnsignedInt(offset + 0x4, off);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::OffsetToDirectory() -> unsigned int
{
	try
	{
		return OffsetToData() & 0x7FFFFFFF;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::DataIsDirectory() -> bool
{
	try
	{
		if ((OffsetToData() & 0x80000000) == 0x80000000)
			return true;
		return false;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::IsNamedEntry() -> bool
{
	try
	{
		if ((Name() & 0x80000000) == 0x80000000)
			return true;
		return false;
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::IsIdEntry() -> bool
{
	try
	{
		return !IsNamedEntry();
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirectoryEntry::ResolveResourceId(const unsigned int& id) -> std::string
{
	try
	{
		switch (id)
		{
			case (unsigned int)ResourceGroupIdType::Cursor: return "Cursor";
			case (unsigned int)ResourceGroupIdType::Bitmap: return "Bitmap";
			case (unsigned int)ResourceGroupIdType::Icon: return "Icon";
			case (unsigned int)ResourceGroupIdType::Menu: return "Menu";
			case (unsigned int)ResourceGroupIdType::Dialog: return "Dialog";
			case (unsigned int)ResourceGroupIdType::String: return "String";
			case (unsigned int)ResourceGroupIdType::FontDirectory: return "Font Directory";
			case (unsigned int)ResourceGroupIdType::Font: return "Font";
			case (unsigned int)ResourceGroupIdType::Accelerator: return "Accelerator";
			case (unsigned int)ResourceGroupIdType::MessageTable: return "Message Table";
			case (unsigned int)ResourceGroupIdType::GroupCursor: return "Group Cursor";
			case (unsigned int)ResourceGroupIdType::GroupIcon: return "GroupIcon";
			case (unsigned int)ResourceGroupIdType::Version: return "Version";
			case (unsigned int)ResourceGroupIdType::DlgInclude: return "DlgInclude";
			case (unsigned int)ResourceGroupIdType::PlugAndPlay: return "Plug And Play";
			case (unsigned int)ResourceGroupIdType::VXD: return "VXD";
			case (unsigned int)ResourceGroupIdType::AnimatedCurser: return "Animated Curser";
			case (unsigned int)ResourceGroupIdType::AnimatedIcon: return "Animated Icon";
			case (unsigned int)ResourceGroupIdType::HTML: return "HTML";
			case (unsigned int)ResourceGroupIdType::Manifest: return "Manifest";
			default: return "unknown";
		}
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

ImageResourceDirStringU::ImageResourceDirStringU(const std::shared_ptr<BufferFile>& bFile, const long& offset) :
	bFile(bFile), offset(offset)
{
	if (WRONG_LONG(this->offset))
		THROW_EXCEPTION("[ERROR] offset value is wrong.");
}

auto ImageResourceDirStringU::Length() const -> unsigned short
{
	try
	{
		return this->bFile->ReadUnsignedShort(offset);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirStringU::Length(const unsigned short& len) -> void
{
	try
	{
		this->bFile->WriteUnsignedShort(offset, len);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto ImageResourceDirStringU::NameString() const -> std::wstring
{
	try
	{
		return this->bFile->ReadUnicodeString(offset + 2, Length());
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
