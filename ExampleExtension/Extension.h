#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>
#include <string>


struct InfoForExtension
{
	const char* name;
	int64_t value;
};

struct SentenceInfo
{
	const InfoForExtension* infoArray;
	// nullptr marks end of info array
	int64_t operator[](std::string propertyName)
	{
		for (auto info = infoArray; info->name != nullptr; ++info) if (propertyName == info->name) return info->value;
		throw;
	}
};

struct SKIP {};
inline void Skip() { throw SKIP(); }
