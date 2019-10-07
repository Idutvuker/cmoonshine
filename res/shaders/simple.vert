
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 ModelViewProjMat;
uniform mat4 ModelMat;

out struct VS_OUT
{
	vec3 normal;
} vout;

void main()
{
	vout.normal = mat3(ModelMat) * normal;
	gl_Position = ModelViewProjMat *  vec4(position, 1.0);
}
