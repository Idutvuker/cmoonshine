#include "Shader.h"

Shader Shader::loadFromFile(GLenum type, const std::string &filepath) {
	std::ifstream stream(filepath);
	if (!stream.is_open())
		Log::e("Can't open file", filepath);
	
	std::string sdata((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	stream.close();
	
	return Shader(type, sdata.c_str());
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
