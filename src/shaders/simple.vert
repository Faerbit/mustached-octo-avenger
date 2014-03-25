#version 150

in vec2 position;
in vec2 texcoord;
in float marker;

out vec2 Texcoord;
out float Marker;

void main()
{
    Texcoord = texcoord;
    Marker = marker;
    gl_Position = vec4(position, 0.0, 1.0);
}
