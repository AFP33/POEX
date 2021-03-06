#include "../Headers/Utils.h"
#include <functional>

auto Utils::RvaToOffset(const unsigned int& virtualAddress, const std::vector<ImageSectionHeader>& sectionHeaders) -> unsigned int
{
	if (sectionHeaders.size() == 0)
		THROW_OUT_OF_RANGE("[ERROR] Section Header can not be empty.");

	std::function<ImageSectionHeader(std::vector<ImageSectionHeader>, unsigned long)> FindSectionFromRva = [&](std::vector<ImageSectionHeader> sectionHeaders, unsigned long relVirtualAddress)
	{
		for (auto imageSectionHeader : sectionHeaders)
			if (relVirtualAddress >= imageSectionHeader.VirtualAddress() && relVirtualAddress < imageSectionHeader.VirtualAddress() + imageSectionHeader.VirtualSize())
				return imageSectionHeader;

		for (auto i = sectionHeaders.size() - 1; i >= 0; i--)
			if (relVirtualAddress >= sectionHeaders[i].VirtualAddress() && relVirtualAddress <= sectionHeaders[i].VirtualAddress() + sectionHeaders[i].VirtualSize())
				return sectionHeaders[i];

		THROW_EXCEPTION("[ERROR] Section Not Found From RVA.");
	};

	auto section = FindSectionFromRva(sectionHeaders, virtualAddress);

	return virtualAddress - section.VirtualAddress() + section.PointerToRawData();
}
