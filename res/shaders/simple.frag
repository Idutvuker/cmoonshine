

#ifdef TEXTURED
uniform sampler2D tex;
#endif

in VS_DATA
{
	vec3 normal;
	vec2 texCoord;
} _in;

out vec4 FragColor;

const vec3 light_dir = normalize(vec3(1, 2, 1));


void main()
{
	float diffuse = max(0.0, dot(normalize(_in.normal), (light_dir)));
	float ambient = 0.1;

	#ifdef TEXTURED
		FragColor = vec4((diffuse * 0.8 + ambient) * texture(tex, _in.texCoord).rgb, 1.0);
	#else
		FragColor = vec4(vec3(diffuse * 0.8 + ambient), 1.0);
	#endif
}
