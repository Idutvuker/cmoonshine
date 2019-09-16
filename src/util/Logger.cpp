#include "Logger.h"

std::ofstream Log::dfile = std::ofstream("debug.log");
std::ofstream Log::efile = std::ofstream("error.log");

std::ostream& Log::d_ost = std::cout;
std::ostream& Log::e_ost = std::cerr;