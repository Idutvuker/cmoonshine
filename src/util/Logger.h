#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

struct Log 
{
	static std::ostream &d_ost;
	static std::ostream &e_ost;
	
	template <typename T>
	inline static void d(T arg1)
	{
		d_ost << arg1 << '\n';
	}

	template <typename T, typename... Args>
	inline static void d(T arg1, Args... args)
	{
		d_ost << arg1 << ' ';
		d(args...);
	}


	template <typename T>
	inline static void e(T arg1)
	{
		e_ost << arg1 << '\n';
	}

	template <typename T, typename... Args>
	inline static void e(T arg1, Args... args)
	{
		e_ost << arg1 << ' ';
		e(args...);
	}
	
	template<typename T>
	inline static void vec(const std::vector<T> &vector)
	{
		for (auto &T: vector)
			d_ost << T << ' ';
		d_ost << '\n';
	}
	
	
private:
	static std::ofstream dfile;
	static std::ofstream efile;
};