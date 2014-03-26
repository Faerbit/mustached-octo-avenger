#version 150

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float time;

void main()
{   
    vec4 texColor = mix(texture(texKitten, Texcoord),
        texture(texPuppy, Texcoord), time);
    outColor = vec4(Color, 1.0)*texColor;
}
