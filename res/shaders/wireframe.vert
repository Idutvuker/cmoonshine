
#attribute vec3 position
//layout (location = 0) in vec3 position;

uniform mat4 ModelViewProjMat;

void main()
{
    gl_Position = ModelViewProjMat * vec4(position, 1.0);
}
