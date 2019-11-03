#pragma once

#include <GL/glew.h>
#include <string>


class Texture
{
	GLuint texture;
public:
	Texture(const std::string &filepath);
	
	friend class BaseMaterial;
};


