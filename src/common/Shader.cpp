#include "Shader.h"
#include <string>
#include <vector>

inline std::string readToken(const std::string &str, int &from)
{
	std::string token;
	token.reserve(20);
	
	while(str[from] != ' ' && str[from] != '\n')
	{
		token += str[from];
		from++;
	}
	from++;
	return token;
}


std::string Shader::preprocess(const std::string &src)
{
	//Log::d(src);
	
	using namespace std;
	vector<pair<string, string::const_iterator>> tokens(1);
	tokens.reserve(100);
	
	auto it = src.begin();
	int i = 0;
	
	while (it != src.end())
	{
		char c = *it;
		//Log::d(c);
		if (c == '\n' || c == '\t' || c == ' ')
		{
			if (!tokens[i].first.empty())
			{
				tokens[i].second = it;
				//Log::d(it - src.begin());
				i++;
				tokens.emplace_back();
			}
		} else
			tokens[i].first += c;
		
		++it;
	}
	
	tokens.resize(tokens.size() - 1);
	
	std::string res;
	auto vit = tokens.begin();
	auto from = src.begin();
	
	while(vit != tokens.end())
	{
		if (vit->first == "#attribute")
		{
			int location = std::stoi((vit + 1)->first);
			string type = (vit + 2)->first;
			string name = (vit + 3)->first;
			
			//Log::d("attribute", location, type, name);
			res.append("layout(location=").append(to_string(location))
			.append(") in ").append(type).append(" ").append(name).append(";");
			
			vit += 3;
		}
		
		else
		{
			res.append(from, vit->second);
		}
		from = vit->second;
		++vit;
	}
	res += '\n';
	
	
	return res;
}

std::string Shader::preprocessLayout(const std::string &src, std::vector<VertexAttrib> &attribs)
{
	int i = 0;
	while ((src[i] == '\n' || src[i] == ' ') && i < src.size()) i++;
	
	std::string res;
	
	while (src.compare(i, 10, "#attribute") == 0)
	{
		i += 11;
		
		//int location = std::stoi(readToken(src, i));
		std::string type = readToken(src, i);
		std::string name = readToken(src, i);
		
		GLenum gl_type = GL_FLOAT;
		int size = 1;
		
		if (type == "vec2")
			gl_type = GL_FLOAT, size = 2;
		else if (type == "vec3")
			gl_type = GL_FLOAT, size = 3;
		else if (type == "vec4")
			gl_type = GL_FLOAT, size = 4;
		else if (type == "float")
			gl_type = GL_FLOAT;
		else if (type == "int")
			gl_type = GL_INT;
		else if (type == "bool")
			gl_type = GL_BOOL;
		else if (type == "uint")
			gl_type = GL_UNSIGNED_INT;
		else
			Log::e("#attribute type is not supported");
		
		int index = attribs.size();
		attribs.push_back({index, size, gl_type});
		
		res.append("layout(location=").append(std::to_string(index))
		.append(") in ").append(type).append(" ").append(name).append(";\n");
		
		while (src[i] == '\n' || src[i] == ' ') i++;
	}
	
	res.append(src, i);
	
	return res;
}


Shader::Shader(GLenum type, const std::string &src)
{
	
	//std::string str = header + (type == GL_VERTEX_SHADER ? preprocessLayout(body) : body);
	const char *src_ca = src.data();
	
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &src_ca, NULL);
	
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

