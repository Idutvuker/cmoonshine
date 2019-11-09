

uniform sampler2D ground;
uniform sampler2D rocks;

in GS_DATA
{
    vec3 wpos;
	vec3 normal;
} _in;

out vec4 FragColor;

const vec3 light_dir = normalize(vec3(1, 6, 0.8));

vec3 triplanar(float scale)
{
    vec3 YZplane = texture(rocks, _in.wpos.yz * scale).rgb;
    vec3 XZplane = texture(ground, _in.wpos.xz * scale).rgb;
    vec3 XYplane = texture(rocks, _in.wpos.xy * scale).rgb;

    vec3 blending = abs(_in.normal);
    blending /= (blending.x + blending.y + blending.z);

    return YZplane * blending.x + XZplane * blending.y + XYplane * blending.z;
}

void main()
{
	float diffuse = max(0.0, dot(normalize(_in.normal), (light_dir)));
	float ambient = 0.1;
    vec3 color = triplanar(0.15);

	FragColor = vec4((diffuse * 0.8 + ambient) * color, 1.0);
}
