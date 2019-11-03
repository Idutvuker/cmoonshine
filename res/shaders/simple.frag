

uniform sampler2D tex;



in VS_DATA
{
	vec3 normal;
	vec2 texCoord;
} _in;

out vec4 _fragColor;

const vec3 light_dir = normalize(vec3(1, 2, 1));


void main()
{
	float diffuse = max(0.0, dot(normalize(_in.normal), (light_dir)));
	float ambient = 0.1;

	_fragColor = vec4((diffuse * 0.8 + ambient) * texture(tex, _in.texCoord).rgb, 1.0);
}
