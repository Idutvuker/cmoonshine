#pragma once

#include <string>
#include <fstream>
#include "Logger.h"


class FileReader
{
public:
	static inline std::string readText(const std::string &filepath)
	{
		std::ifstream stream(filepath);
		if (!stream.is_open())
			Log::e("Can't open file", filepath);
		
		std::string sdata{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
		stream.close();
		return sdata;
	}
};


