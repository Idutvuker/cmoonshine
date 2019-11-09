#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "../util/Logger.h"

Texture::Texture(const std::string &filepath)
{
	int x, y, n;
	unsigned char *data = stbi_load(filepath.data(), &x, &y, &n, STBI_rgb);
	Log::d(filepath, n);
	glGenTextures(1, &texture);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	//glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}
