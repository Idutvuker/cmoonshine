#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "VertexAttribSetup.h"
#include "Shader.h"
#include "../util/glmath.h"
#include "../system/RenderContext.h"

#define MACRO_DEFUNIFORM_ENUM(DO) \
	DO(ModelViewProjMat) \
	DO(ModelViewMat) \
	DO(ViewProjMat) \
	DO(ModelMat) \
	DO(ViewMat) \
	DO(ProjMat)

#define MACRO_MAKE_STRING(VAR) #VAR,

class BaseMaterial
{
private:

	#define MACRO_MAKE_ENUM(VAR) VAR,
	enum DefUniform
	{
		MACRO_DEFUNIFORM_ENUM(MACRO_MAKE_ENUM)
		_ENUM_SIZE
	};
	#undef MACRO_MAKE_ENUM

	static const char * const DefUniformNames[];
	std::vector<GLint> DefUniformLocations = std::vector<GLint>(DefUniform::_ENUM_SIZE, -1);


	GLuint program;

	void setUniform(GLint location, const mat4 &value);

	void setUniform(GLint location, const mat3 &value);

	void setUniform(GLint location, const vec4 &value);

	void setUniform(GLint location, const vec3 &value);

	void setUniform(GLint location, GLfloat value);

	std::map<std::string, GLint> locTable;

	void loadUniforms();

public:
	VertexAttribSetup vertexAttribSetup;
	


	BaseMaterial(
				const std::string &vertexShaderFilepath,
				const std::string &fragmentShaderFilepath,
				const std::vector<VertexDataType> &dataTypes,
				const std::string &header = std::string());

	void use();

	void prepare(const RenderContext &context);
	
	
	template <typename T>
	void setShaderUniform(const std::string name, const T &value)
	{
		auto it = locTable.find(name);
		if (it != locTable.end())
		{
			glUseProgram(program);
			setUniform(it->second, value);
		}
	}
	
	virtual ~BaseMaterial();
};




//#undef MACRO_MAKE_STRING

//#undef MACRO_DEFUNIFORM_ENUM