#version 330 core

in struct VS_OUT
{
	vec3 normal;
} vout;

out vec4 color;

const vec3 light_dir = normalize(vec3(1, 2, 1));

void main()
{
	float diffuse = max(0.0, dot(normalize(vout.normal), (light_dir)));
	float ambient = 0.1;
	color = vec4(vec3(diffuse * 0.8 + ambient), 1.0);
}
