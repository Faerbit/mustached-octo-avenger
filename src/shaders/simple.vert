#version 150

in vec2 position;
in vec2 texcoord;
in float marker;

out vec2 Texcoord;
out float Marker;

uniform mat4 trans;

void main()
{
    Texcoord = texcoord;
    Marker = marker;
    gl_Position = trans*vec4(position, 0.0, 1.0);
}
