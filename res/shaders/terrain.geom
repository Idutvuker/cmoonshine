

const int EDGE_TABLE[256] = int[](
0x0, 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
0x190, 0x99, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
0x230, 0x339, 0x33, 0x13a, 0x636, 0x73f, 0x435, 0x53c,
0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
0x3a0, 0x2a9, 0x1a3, 0xaa, 0x7a6, 0x6af, 0x5a5, 0x4ac,
0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
0x460, 0x569, 0x663, 0x76a, 0x66, 0x16f, 0x265, 0x36c,
0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff, 0x3f5, 0x2fc,
0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55, 0x15c,
0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc,
0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
0xcc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
0x15c, 0x55, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
0x2fc, 0x3f5, 0xff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
0x36c, 0x265, 0x16f, 0x66, 0x76a, 0x663, 0x569, 0x460,
0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa, 0x1a3, 0x2a9, 0x3a0,
0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33, 0x339, 0x230,
0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99, 0x190,
0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0);

const uint TRI_TABLE[512] = uint[](
0xdddddddd, 0xdddddddd,
0x083ddddd, 0xdddddddd,
0x019ddddd, 0xdddddddd,
0x183981dd, 0xdddddddd,
0x12addddd, 0xdddddddd,
0x08312add, 0xdddddddd,
0x92a029dd, 0xdddddddd,
0x2832a8a9, 0x8ddddddd,
0x3b2ddddd, 0xdddddddd,
0x0b28b0dd, 0xdddddddd,
0x19023bdd, 0xdddddddd,
0x1b219b98, 0xbddddddd,
0x3a1ba3dd, 0xdddddddd,
0x0a108a8b, 0xaddddddd,
0x3903b9ba, 0x9ddddddd,
0x98aa8bdd, 0xdddddddd,
0x478ddddd, 0xdddddddd,
0x430734dd, 0xdddddddd,
0x019847dd, 0xdddddddd,
0x41947173, 0x1ddddddd,
0x12a847dd, 0xdddddddd,
0x34730412, 0xaddddddd,
0x92a90284, 0x7ddddddd,
0x2a929727, 0x3794dddd,
0x8473b2dd, 0xdddddddd,
0xb47b2420, 0x4ddddddd,
0x90184723, 0xbddddddd,
0x47b94b9b, 0x2921dddd,
0x3a13ba78, 0x4ddddddd,
0x1ba14b10, 0x47b4dddd,
0x47890b9b, 0xab03dddd,
0x47b4b99b, 0xaddddddd,
0x954ddddd, 0xdddddddd,
0x954083dd, 0xdddddddd,
0x054150dd, 0xdddddddd,
0x85483531, 0x5ddddddd,
0x12a954dd, 0xdddddddd,
0x30812a49, 0x5ddddddd,
0x52a54240, 0x2ddddddd,
0x2a532535, 0x4348dddd,
0x95423bdd, 0xdddddddd,
0x0b208b49, 0x5ddddddd,
0x05401523, 0xbddddddd,
0x21525828, 0xb485dddd,
0xa3ba1395, 0x4ddddddd,
0x4950818a, 0x18badddd,
0x54050b5b, 0xab03dddd,
0x54858aa8, 0xbddddddd,
0x978579dd, 0xdddddddd,
0x93095357, 0x3ddddddd,
0x07801715, 0x7ddddddd,
0x153357dd, 0xdddddddd,
0x978957a1, 0x2ddddddd,
0xa1295053, 0x0573dddd,
0x80282585, 0x7a52dddd,
0x2a525335, 0x7ddddddd,
0x7957893b, 0x2ddddddd,
0x95797292, 0x027bdddd,
0x23b01817, 0x8157dddd,
0xb21b1771, 0x5ddddddd,
0x958857a1, 0x3a3bdddd,
0x5705097b, 0x010aba0d,
0xba0b03a5, 0x0807570d,
0xba57b5dd, 0xdddddddd,
0xa65ddddd, 0xdddddddd,
0x0835a6dd, 0xdddddddd,
0x9015a6dd, 0xdddddddd,
0x1831985a, 0x6ddddddd,
0x165261dd, 0xdddddddd,
0x16512630, 0x8ddddddd,
0x96590602, 0x6ddddddd,
0x59858252, 0x6328dddd,
0x23ba65dd, 0xdddddddd,
0xb08b20a6, 0x5ddddddd,
0x01923b5a, 0x6ddddddd,
0x5a61929b, 0x298bdddd,
0x63b65351, 0x3ddddddd,
0x08b0b505, 0x15b6dddd,
0x3b603606, 0x5059dddd,
0x65969bb9, 0x8ddddddd,
0x5a6478dd, 0xdddddddd,
0x43047365, 0xaddddddd,
0x1905a684, 0x7ddddddd,
0xa6519717, 0x3794dddd,
0x61265147, 0x8ddddddd,
0x12552630, 0x4347dddd,
0x84790506, 0x5026dddd,
0x73979432, 0x9596269d,
0x3b2784a6, 0x5ddddddd,
0x5a647242, 0x027bdddd,
0x01947823, 0xb5a6dddd,
0x9219b294, 0xb7b45a6d,
0x8473b535, 0x15b6dddd,
0x51b5b610, 0xb7b404bd,
0x05906503, 0x6b63847d,
0x65969b47, 0x97b9dddd,
0xa4964add, 0xdddddddd,
0x4a649a08, 0x3ddddddd,
0xa01a6064, 0x0ddddddd,
0x83181686, 0x461adddd,
0x14912426, 0x4ddddddd,
0x30812924, 0x9264dddd,
0x024426dd, 0xdddddddd,
0x83282442, 0x6ddddddd,
0xa49a64b2, 0x3ddddddd,
0x08228b49, 0xa4a6dddd,
0x3b201606, 0x461adddd,
0x64161a48, 0x121b8b1d,
0x96493691, 0x3b63dddd,
0x8b1810b6, 0x1914641d,
0x3b636006, 0x4ddddddd,
0x648b68dd, 0xdddddddd,
0x7a678a89, 0xaddddddd,
0x0730a709, 0xa67adddd,
0xa671a717, 0x8180dddd,
0xa67a7117, 0x3ddddddd,
0x12616818, 0x9867dddd,
0x26929167, 0x9093739d,
0x78070660, 0x2ddddddd,
0x732672dd, 0xdddddddd,
0x23ba68a8, 0x9867dddd,
0x20727b09, 0x767a9a7d,
0x1801781a, 0x767a23bd,
0xb21b17a6, 0x1671dddd,
0x89686791, 0x6b63136d,
0x091b67dd, 0xdddddddd,
0x7807063b, 0x0b60dddd,
0x7b6ddddd, 0xdddddddd,
0x76bddddd, 0xdddddddd,
0x308b76dd, 0xdddddddd,
0x019b76dd, 0xdddddddd,
0x819831b7, 0x6ddddddd,
0xa126b7dd, 0xdddddddd,
0x12a3086b, 0x7ddddddd,
0x2902a96b, 0x7ddddddd,
0x6b72a3a8, 0x3a98dddd,
0x723627dd, 0xdddddddd,
0x70876062, 0x0ddddddd,
0x27623701, 0x9ddddddd,
0x16218619, 0x8876dddd,
0xa76a1713, 0x7ddddddd,
0xa7617a18, 0x7108dddd,
0x03707a0a, 0x96a7dddd,
0x76a7a88a, 0x9ddddddd,
0x684b86dd, 0xdddddddd,
0x36b30604, 0x6ddddddd,
0x86b84690, 0x1ddddddd,
0x94696393, 0x1b36dddd,
0x6846b82a, 0x1ddddddd,
0x12a30b06, 0xb046dddd,
0x4b846b02, 0x92a9dddd,
0xa93a3294, 0x3b36463d,
0x82384246, 0x2ddddddd,
0x042462dd, 0xdddddddd,
0x19023424, 0x6438dddd,
0x19414224, 0x6ddddddd,
0x81386184, 0x66a1dddd,
0xa10a0660, 0x4ddddddd,
0x4634386a, 0x3039a93d,
0xa946a4dd, 0xdddddddd,
0x49576bdd, 0xdddddddd,
0x083495b7, 0x6ddddddd,
0x50154076, 0xbddddddd,
0xb7683435, 0x4315dddd,
0x954a1276, 0xbddddddd,
0x6b712a08, 0x3495dddd,
0x76b54a42, 0xa402dddd,
0x34835432, 0x5a52b76d,
0x72376254, 0x9ddddddd,
0x95408606, 0x2687dddd,
0x36237615, 0x0540dddd,
0x62868721, 0x8485158d,
0x954a1617, 0x6137dddd,
0x16a17610, 0x7870954d,
0x40a4a503, 0xa6a737ad,
0x76a7a854, 0xa48adddd,
0x6956b9b8, 0x9ddddddd,
0x36b06305, 0x6095dddd,
0x0b805b01, 0x556bdddd,
0x6b363553, 0x1ddddddd,
0x12a95b9b, 0x8b56dddd,
0x0b306b09, 0x656912ad,
0xb85b5680, 0x5a52025d,
0x6b36352a, 0x3a53dddd,
0x58952856, 0x2382dddd,
0x95696006, 0x2ddddddd,
0x15818056, 0x8382628d,
0x156216dd, 0xdddddddd,
0x13616a38, 0x6569896d,
0xa10a0695, 0x0560dddd,
0x03856add, 0xdddddddd,
0xa56ddddd, 0xdddddddd,
0xb5a75bdd, 0xdddddddd,
0xb5ab7583, 0x0ddddddd,
0x5b75ab19, 0x0ddddddd,
0xa75ab798, 0x1831dddd,
0xb12b7175, 0x1ddddddd,
0x08312717, 0x572bdddd,
0x97592790, 0x22b7dddd,
0x75272b59, 0x2328982d,
0x25a23537, 0x5ddddddd,
0x82085287, 0x5a25dddd,
0x9015a353, 0x73a2dddd,
0x98292187, 0x2a25752d,
0x135375dd, 0xdddddddd,
0x08707117, 0x5ddddddd,
0x90393553, 0x7ddddddd,
0x987597dd, 0xdddddddd,
0x5845a8ab, 0x8ddddddd,
0x5045b05a, 0xbb30dddd,
0x01984a8a, 0xba45dddd,
0xab4a45b3, 0x4941314d,
0x2512852b, 0x8458dddd,
0x04b0b345, 0xb2b151bd,
0x0250592b, 0x5458b85d,
0x9452b3dd, 0xdddddddd,
0x25a35234, 0x5384dddd,
0x5a252442, 0x0ddddddd,
0x3a235a38, 0x5458019d,
0x5a252419, 0x2942dddd,
0x84585335, 0x1ddddddd,
0x045105dd, 0xdddddddd,
0x84585390, 0x5035dddd,
0x945ddddd, 0xdddddddd,
0x4b749b9a, 0xbddddddd,
0x0834979b, 0x79abdddd,
0x1ab1b414, 0x074bdddd,
0x3143481a, 0x474bab4d,
0x4b79b492, 0xb912dddd,
0x9749b791, 0xb2b1083d,
0xb74b4224, 0x0ddddddd,
0xb74b4283, 0x4324dddd,
0x29a27923, 0x7749dddd,
0x9a7974a2, 0x7870207d,
0x37a3a274, 0xa1a040ad,
0x1a2874dd, 0xdddddddd,
0x49141771, 0x3ddddddd,
0x49141708, 0x1871dddd,
0x403743dd, 0xdddddddd,
0x487ddddd, 0xdddddddd,
0x9a8ab8dd, 0xdddddddd,
0x30939bb9, 0xaddddddd,
0x01a0a88a, 0xbddddddd,
0x31ab3add, 0xdddddddd,
0x12b1b99b, 0x8ddddddd,
0x30939b12, 0x92b9dddd,
0x02b80bdd, 0xdddddddd,
0x32bddddd, 0xdddddddd,
0x23828aa8, 0x9ddddddd,
0x9a2092dd, 0xdddddddd,
0x23828a01, 0x81a8dddd,
0x1a2ddddd, 0xdddddddd,
0x138918dd, 0xdddddddd,
0x091ddddd, 0xdddddddd,
0x038ddddd, 0xdddddddd,
0xdddddddd, 0xdddddddd);

const vec3 VOXEL_POSITION[8] = vec3[](
    vec3(0, 0, 0),
    vec3(1, 0, 0),
    vec3(1, 0, 1),
    vec3(0, 0, 1),

    vec3(0, 1, 0),
    vec3(1, 1, 0),
    vec3(1, 1, 1),
    vec3(0, 1, 1)
);

const int EDGE_ORDER[12 * 2] = int[](
    0, 1,
    1, 2,
    3, 2,
    0, 3,

    4, 5,
    5, 6,
    7, 6,
    4, 7,

    0, 4,
    1, 5,
    2, 6,
    3, 7
);

const int EDGE_OFFSET[12] = int[](
    0,      3*DIMZ*DIMY+1,          3,                  1,
    3*DIMZ, 3*DIMZ*DIMY+3*DIMZ+1,   3*DIMZ+3,           3*DIMZ+1,
    2,      3*DIMZ*DIMY+2,          3*DIMZ*DIMY+3+2,    3+2
);

int getI(in int x, in int y, in int z, int edge)
{
    return 3 * int(x * DIMZ * DIMY + y * DIMZ + z) + EDGE_OFFSET[edge];
}

uint triTable(in int row, in int column)
{
    int cm8 = column & 7;
    return (TRI_TABLE[row * 2 + column / 8] >> uint(28 - cm8 * 4)) & uint(15);
}

layout (points) in;
layout (triangle_strip, max_vertices = 15) out;

uniform mat4 ModelViewProjMat;
uniform usamplerBuffer data;

const float isolevel = ISOLEVEL;
in int gs_bits[];

out vec3 _normal;

void unpackVertex(in uint vert, out float alpha, out vec3 normal)
{
    uint epos = vert >> 24;
    alpha = epos / 255.f;

    float nx = (vert >> uint(11) & uint(2047)) / 1023.f - 1.f;
    float ny = (vert & uint(2047)) / 1023.f - 1.f;
    bool n_neg_z = ((vert & uint(1 << 23)) != uint(0));
    float nz = sqrt(1.f - min(nx * nx + ny * ny, 1.f));
    if (n_neg_z)
        nz *= -1.f;

    normal = vec3(nx, ny, nz);
}

void main()
{
    vec4 pos = gl_in[0].gl_Position;
    int x = int(pos.x + 0.5);
    int y = int(pos.y + 0.5);
    int z = int(pos.z + 0.5);

    vec3 vertices[12];
    vec3 normals[12];

    int bits = gs_bits[0];
    int power = 1;

    int edges = EDGE_TABLE[bits];


    power = 1;

    for (int i = 0; i < 12; i++)
    {
        if ((edges & power) != 0)
        {
            int v1 = EDGE_ORDER[i * 2];
            int v2 = EDGE_ORDER[i * 2 + 1];

            int id = getI(x, y, z, i);
            float alpha;

            unpackVertex(texelFetch(data, id).r, alpha, normals[i]);

            vertices[i] = mix(VOXEL_POSITION[v1], VOXEL_POSITION[v2], alpha);
        }

        power <<= 1;
    }


    uint triT1 = TRI_TABLE[bits * 2];
    uint triT2 = TRI_TABLE[bits * 2 + 1];

    uint triangles[16];
    for (int i = 0; i < 8; i++)
        triangles[i] = (triT1 >> uint(28 - i * 4)) & uint(15);

    for (int i = 0; i < 8; i++)
        triangles[8 + i] = (triT2 >> uint(28 - i * 4)) & uint(15);



    int i = 0;
    while(triangles[i] != uint(13))
    {
        uint i1 = triangles[i];
        uint i2 = triangles[i + 1];
        uint i3 = triangles[i + 2];

        vec3 v1 = vertices[i1];
        vec3 v2 = vertices[i2];
        vec3 v3 = vertices[i3];

        vec3 tmp1 = v2 - v1;
        vec3 tmp2 = v3 - v1;

        //_normal = normalize(cross(tmp1, tmp2));
        _normal = normals[i1];
        gl_Position = ModelViewProjMat * (pos + vec4(v1, 0));
        EmitVertex();

        _normal = normals[i2];
        gl_Position = ModelViewProjMat * (pos + vec4(v2, 0));
        EmitVertex();

        _normal = normals[i3];
        gl_Position = ModelViewProjMat * (pos + vec4(v3, 0));
        EmitVertex();

        EndPrimitive();

        i += 3;
    }


}