
#attribute vec3 _position
#attribute vec3 _normal
#attribute vec2 _texCoord

uniform mat4 ModelViewProjMat;
uniform mat4 ModelMat;

//layout (location = 0) in vec3 _position;
//layout (location = 1) in vec3 _normal;
//layout (location = 2) in vec2 _texCoord;

out VS_DATA
{
	vec3 normal;
	vec2 texCoord;
} _out;

void main()
{
	_out.texCoord = _texCoord;
	_out.normal = mat3(ModelMat) * _normal;
	gl_Position = ModelViewProjMat *  vec4(_position, 1.0);
}
