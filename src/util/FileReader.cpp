#include <fstream>
#include "FileReader.h"
#include "Logger.h"

std::string FileReader::readFile(const std::string &filepath)
{
	std::ifstream stream(filepath);
	if (!stream.is_open())
		Log::e("Can't open file", filepath);
	
	std::string sdata{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
	stream.close();
	return sdata;
}
