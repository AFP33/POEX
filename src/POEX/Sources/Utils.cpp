#include "../Headers/Utils.h"
#include <functional>

auto Utils::VaToOffset(const unsigned long& virtualAddress, const std::vector<std::shared_ptr<ImageSectionHeader>>& sectionHeaders) -> unsigned long
{
	try
	{
		auto firstObj = sectionHeaders.front();
		auto rva = virtualAddress - firstObj->ImageBaseAddress();
		return Utils::RvaToOffset(rva, sectionHeaders);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

auto Utils::RvaToOffset(const unsigned int& virtualAddress, const std::vector<std::shared_ptr<ImageSectionHeader>>& sectionHeaders) -> unsigned int
{
	try
	{
		if (sectionHeaders.size() == 0)
			THROW_OUT_OF_RANGE("[ERROR] Section Header can not be empty.");

		std::function<std::shared_ptr<ImageSectionHeader>(std::vector<std::shared_ptr<ImageSectionHeader>>, unsigned long)> FindSectionFromRva =
			[&](std::vector<std::shared_ptr<ImageSectionHeader>> sectionHeaders, unsigned long relVirtualAddress)
		{
			for (auto imageSectionHeader : sectionHeaders)
				if (relVirtualAddress >= imageSectionHeader->VirtualAddress() && relVirtualAddress < imageSectionHeader->VirtualAddress() + imageSectionHeader->VirtualSize())
					return imageSectionHeader;

			for (auto i = sectionHeaders.size() - 1; i >= 0; i--)
				if (relVirtualAddress >= sectionHeaders[i]->VirtualAddress() && relVirtualAddress <= sectionHeaders[i]->VirtualAddress() + sectionHeaders[i]->VirtualSize())
					return sectionHeaders[i];

			THROW_EXCEPTION("[ERROR] Section Not Found From RVA.");
		};

		auto section = FindSectionFromRva(sectionHeaders, virtualAddress);

		return virtualAddress - section->VirtualAddress() + section->PointerToRawData();
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}
