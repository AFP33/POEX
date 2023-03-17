#pragma once

#include "ImageSectionHeader.h"

class Utils
{
public:
	auto static VaToOffset(const unsigned long& virtualAddress, const std::vector<ImageSectionHeader>& sectionHeaders) -> unsigned long;
	auto static RvaToOffset(const unsigned int& virtualAddress, const std::vector<ImageSectionHeader>& sectionHeaders)->unsigned int;

private:
	Utils() = default;
	~Utils() = default;
};