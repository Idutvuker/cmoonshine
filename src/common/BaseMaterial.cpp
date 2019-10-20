#include "BaseMaterial.h"
#include "../util/FileReader.h"

const char * const BaseMaterial::DefUniformNames[] = {
		MACRO_DEFUNIFORM_ENUM(MACRO_MAKE_STRING)
};

void BaseMaterial::prepare(const RenderContext &context) {
	use();
	
	int loc;
	
	if ((loc = DefUniformLocations[ModelViewProjMat]) != -1)
		setUniform(loc, context.ViewProj * context.Model);
	
	if ((loc = DefUniformLocations[ModelViewMat]) != -1)
		setUniform(loc, context.View * context.Model);
	
	if ((loc = DefUniformLocations[ViewProjMat]) != -1)
		setUniform(loc, context.ViewProj);
	
	if ((loc = DefUniformLocations[ModelMat]) != -1)
		setUniform(loc, context.Model);
	
	if ((loc = DefUniformLocations[ViewMat]) != -1)
		setUniform(loc, context.View);
	
	if ((loc = DefUniformLocations[ProjMat]) != -1)
		setUniform(loc, context.Proj);
}

void BaseMaterial::use() {
	glUseProgram(program);
}



BaseMaterial::BaseMaterial(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath,
						   const std::string &geometryShaderFilepath, const std::vector<std::string> &defines)
{
	std::string header = "#version 330 core\n";
	for (auto &def : defines)
		header += "#define " + def + '\n';
	
	program = glCreateProgram();
	
	std::string vs_src = header + FileReader::readText(vertexShaderFilepath);
	Shader vertexShader = Shader(GL_VERTEX_SHADER, vs_src.data());
	glAttachShader(program, vertexShader.shader);
	
	
	std::string fs_src = header + FileReader::readText(fragmentShaderFilepath);
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fs_src.data());
	glAttachShader(program, fragmentShader.shader);
	
	if (!geometryShaderFilepath.empty())
	{
		std::string gs_src = header + FileReader::readText(geometryShaderFilepath);
		Shader geometryShader = Shader(GL_GEOMETRY_SHADER, gs_src.data());
		glAttachShader(program, geometryShader.shader);
	}
	
	glLinkProgram(program);
	
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(program, sizeof(infoLog), nullptr, infoLog);
		
		Log::e(vertexShaderFilepath + " <-> " + fragmentShaderFilepath + " program linking error:\n", infoLog);
	}
	
	vertexShader.deleteShader();
	fragmentShader.deleteShader();
	
	loadAttributes();
	loadUniforms();
}

void BaseMaterial::setUniform(GLint location, const mat4 &value) {
	glUniformMatrix4fv(location, 1, false, value_ptr(value));
}

void BaseMaterial::setUniform(GLint location, const mat3 &value) {
	glUniformMatrix3fv(location, 1, false, value_ptr(value));
}

void BaseMaterial::setUniform(GLint location, const vec4 &value) {
	glUniform4fv(location, 1, value_ptr(value));
}

void BaseMaterial::setUniform(GLint location, const vec3 &value) {
	glUniform3fv(location, 1, value_ptr(value));
}

void BaseMaterial::setUniform(GLint location, GLfloat value) {
	glUniform1fv(location, 1, &value);
}

void BaseMaterial::setUniform(GLint location, int value) {
	glUniform1i(location, value);
}


void BaseMaterial::loadAttributes()
{
	GLint count;
	
	GLint size;
	GLenum type;
	
	const GLsizei bufSize = 16;
	GLchar name[bufSize];
	GLsizei length;
	
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
	attribs.resize(count);
	
	int real_count = 0;
	for (int i = 0; i < count; i++)
	{
		glGetActiveAttrib(program, (GLuint) i, bufSize, &length, &size, &type, name);
		
		switch (type)
		{
			case GL_FLOAT_VEC4:
				type = GL_FLOAT;
				size *= 4;
				break;
			
			case GL_FLOAT_VEC3:
				type = GL_FLOAT;
				size *= 3;
				break;
				
			case GL_FLOAT_VEC2:
				type = GL_FLOAT;
				size *= 2;
				break;
			
			case GL_FLOAT:
			case GL_INT:
			case GL_UNSIGNED_INT:
			case GL_HALF_FLOAT:
			case GL_BOOL:
				break;
			
			default:
				Log::e("Shader attribute uses unsupported type. Name, type, size:", name, type, size);
		}
		
		
		int loc = glGetAttribLocation(program, name);
		
		if (loc != -1)
		{
			attribs[loc] = {loc, size, type, 0, 0};
			real_count++;
		}
	}
	attribs.resize(real_count);
}


void BaseMaterial::loadUniforms()
{
	int count;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	
	const GLsizei bufsize = 32;
	GLsizei length;
	GLchar name[bufsize];
	
	GLint size;
	GLenum type;
	
	for (int i = 0; i < count; i++)
	{
		glGetActiveUniform(program, (GLuint) i, bufsize, &length, &size, &type, name);
		
		GLint location = glGetUniformLocation(program, name);
		
		
		bool def = false;
		for (int j = 0; j < DefUniform::_ENUM_SIZE; j++)
		{
			if (strcmp(DefUniformNames[j], name) == 0)
			{
				DefUniformLocations[j] = location;
				def = true;
				break;
			}
		}
		
		if (!def)
			locTable.insert({ name,  location});
	}
}

BaseMaterial::~BaseMaterial(){}

