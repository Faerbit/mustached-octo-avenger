#version 150

in vec3 position;
in vec2 texcoord;
in vec3 color;

out vec2 Texcoord;
out vec3 Color;

uniform vec3 overrideColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Color = overrideColor * color;
    Texcoord = texcoord;
    gl_Position = projection*view*model*vec4(position, 1.0);
}
