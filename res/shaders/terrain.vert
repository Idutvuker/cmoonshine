

layout (location = 0) in uint data;

uniform mat4 ModelViewProjMat;
uniform mat4 ModelMat;

const float scale = 1;

out struct VS_OUT
{
	vec3 normal;
} vout;

float to_float(in uint a)
{
    return float(a) / 127.f - 1.f;
}

void main()
{
	int dir = gl_VertexID % 3;
	int id = gl_VertexID / 3;
	float x = id / (DIMZ * DIMY);
	float y = id / DIMZ % DIMY;
	float z = id % DIMZ;

	float edgePos = data >> 24;

	float t = edgePos / 255.f;

	if (dir == 0)
		x += t;
	else if (dir == 1)
		z += t;
	else
		y += t;

	vec4 position = vec4(x * scale, y * scale, z * scale, 1.0);

	float nx = (data >> uint(11) & uint(2047)) / 1023.f - 1.f;
	float ny = (data & uint(2047)) / 1023.f - 1.f;
	bool n_neg_z = ((data & uint(1 << 23)) != uint(0));
	float nz = sqrt(1.f - min(nx * nx + ny * ny, 1.f));
	if (n_neg_z)
		nz *= -1.f;


    vec3 normal = vec3(nx, ny, nz);

//	normal = vec3(0 ,0 ,0);
//	if (isnan(nx))
//		normal += vec3(1, 0, 0);
//	if (isnan(ny))
//		normal += vec3(0, 0, 0);
////	if (isnan(nz))
////		normal += vec3(0, 0, 1);

	vout.normal = mat3(ModelMat) * normal;
	gl_Position = ModelViewProjMat * position;
}
