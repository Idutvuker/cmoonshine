#attribute int _bits

uniform mat4 ModelViewProjMat;

const float scale = 1;

//layout (location = 0) in int _bits;

out VS_DATA
{
	int bits;
} _out;


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
	_out.bits = _bits;
}
