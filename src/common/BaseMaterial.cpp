#include "BaseMaterial.h"
#include "../util/FileReader.h"

const char * const BaseMaterial::DefUniformNames[] = {
		MACRO_DEFUNIFORM_ENUM(MACRO_MAKE_STRING)
};

void BaseMaterial::prepare(const RenderContext &context) {
	use();
	
	for (GLenum i = 0; i < (GLenum) textures.size(); i++)
	{
		if (textures[i] != nullptr)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]->texture);
			glUniform1i(glGetUniformLocation(program, "tex"), 0);
		}
	}
	
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


bool BaseMaterial::setTexture(const std::string &name, Texture *texture)
{
	int block = (int) textures.size();
	
	auto it = locTable.find(name);
	if (it != locTable.end())
	{
		int slot;
		glGetUniformiv(program, it->second, &slot);
		
		if (slot < 0 && slot >= textures.size())
			return false;
		
		textures[slot] = texture;
		return true;
	}
	
	return false;
}


BaseMaterial::BaseMaterial(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath,
						   const std::string &geometryShaderFilepath, const std::vector<std::string> &defines)
{
	std::string header = "#version 330 core\n";
	for (auto &def : defines)
		header += "#define " + def + '\n';
	
	program = glCreateProgram();
	
	//Log::d(vertexShaderFilepath);
	std::string vs_src = header + Shader::preprocessLayout(FileReader::readText(vertexShaderFilepath), attribs);
	Shader vertexShader = Shader(GL_VERTEX_SHADER, vs_src);
	glAttachShader(program, vertexShader.shader);
	//Log::d("ok");
	
	std::string fs_src = header + FileReader::readText(fragmentShaderFilepath);
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fs_src);
	glAttachShader(program, fragmentShader.shader);
	
	if (!geometryShaderFilepath.empty())
	{
		std::string gs_src = header + FileReader::readText(geometryShaderFilepath);
		Shader geometryShader = Shader(GL_GEOMETRY_SHADER, gs_src);
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
	
	//loadAttributes();
	loadUniforms();
}

BaseMaterial::~BaseMaterial(){}


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
			attribs[loc] = {loc, size, type};
			real_count++;
		}
	}
	attribs.resize(real_count);
}


void BaseMaterial::loadUniforms()
{
	use();
	
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
		
		if (type == GL_SAMPLER_2D)
		{
			setUniform(location, (int) textures.size());
			textures.push_back(nullptr);
		}
		
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

BaseMaterial::BaseMaterial(const BaseMaterial::Definition &def) :
	BaseMaterial(
		def.vertexShaderFilepath,
		def.fragmentShaderFilepath,
		def.geometryShaderFilepath,
		def.defines)
{}




