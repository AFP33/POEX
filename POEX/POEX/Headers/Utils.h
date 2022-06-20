#pragma once

#include "ImageSectionHeader.h"

class Utils
{
public:
	auto static RvaToOffset(const unsigned int& virtualAddress, const std::vector<ImageSectionHeader>& sectionHeaders)->unsigned int;

private:
	Utils() = default;
	~Utils() = default;
};