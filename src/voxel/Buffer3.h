#pragma once

#include "../util/glmath.h"

template <typename T, int sizeX, int sizeY, int sizeZ>
struct Buffer3
{
	T *data;//[sizeX * sizeY * sizeZ];
	
	Buffer3()
	{
		data = new T[sizeX * sizeY * sizeZ]();
	}
	
	const int dimX = sizeX;
	const int dimY = sizeX;
	const int dimZ = sizeX;
	
	inline
	bool inBounds(int x, int y, int z)
	{
		return (x >= 0 && x < sizeX && y >= 0 && y < sizeY && z >=0 && z < sizeZ);
	}
	
	
	inline
	T safeGet(int x, int y, int z, T def = 0)
	{
		if (inBounds(x, y, z))
			return data[rawId(x, y, z)];
		return def;
	}
	
	inline
	void safeSet(int x, int y, int z, T val)
	{
		if (inBounds(x, y, z))
			data[rawId(x, y, z)] = val;
	}
	
	
	
	inline
	T& operator[](uint32 i)
	{
		return data[i];
	}
	
	inline
	T operator[](uint32 i) const
	{
		return data[i];
	}
	
	
	inline
	uint32 rawId(uint32 x, uint32 y, uint32 z) const
	{
		return x * sizeY * sizeZ + y * sizeZ + z;
	}
	
	inline
	uint32 rawId(const ivec3 &v) const
	{
		return v.x * sizeY * sizeZ + v.y * sizeZ + v.z;
	}
	
	inline
	T& operator()(int x, int y, int z)
	{
		return data[rawId(x, y, z)];
	}
	
	inline
	T operator()(int x, int y, int z) const
	{
		return data[rawId(x, y, z)];
	}
	

};


