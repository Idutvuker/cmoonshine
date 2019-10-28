

in vec3 _normal;
out vec4 color;

const vec3 light_dir = normalize(vec3(1, 1, 1));

void main()
{
	float diffuse = max(0.0, dot(normalize(_normal), (light_dir)));
	float ambient = 0.1;
	color = vec4(vec3(diffuse * 0.8 + ambient), 1.0);
	//color = vec4(_normal, 1.0);
}
