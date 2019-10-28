

uniform mat4 ModelViewProjMat;
uniform mat4 ModelMat;

const float scale = 1;

layout (location = 0) in int bits;

out int gs_bits;


float to_float(in uint a)
{
    return float(a) / 127.f - 1.f;
}

void main()
{
	int id = gl_VertexID;
	float x = id / (DIMZ * DIMY);
	float y = id / DIMZ % DIMY;
	float z = id % DIMZ;

	vec4 position = vec4(x, y, z, 1.0);
    gl_Position = position;
	gs_bits = bits;
}
