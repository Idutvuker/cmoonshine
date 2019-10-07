#include "Shader.h"

Shader Shader::loadFromFile(GLenum type, const std::string &filepath, const std::string &header)
{
	std::ifstream stream(filepath);
	if (!stream.is_open())
		Log::e("Can't open file", filepath);
	
	std::string sdata{std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
	
	stream.close();
	
	std::string shaderStr = "#version 330 core\n";
	if (!header.empty())
		shaderStr += header;
	shaderStr += sdata;
	
	return Shader(type, shaderStr.c_str());
}

Shader::Shader(GLenum type, const char *source) {
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	
	glCompileShader(shader);
	
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shader, sizeof(infoLog), 0, infoLog);
		
		Log::e("Shader compilation failed:\n", infoLog);
	}
}

void Shader::attach(GLuint program) {
	glAttachShader(program, shader);
}

void Shader::deleteShader() {
	glDeleteShader(shader);
}
