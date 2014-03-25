#version 150

in vec3 Color;
in vec2 Texcoord;
in float Marker;

out vec4 outColor;

uniform sampler2D texKitten;
uniform sampler2D texPuppy;
uniform float time;

void main()
{
    vec4 colKitten = texture(texKitten, Texcoord);
    vec4 colPuppy  = texture(texPuppy, Texcoord);
    if (Marker != 1.0f)
        outColor = mix(colKitten, colPuppy, time);
    else
    {
        vec4 outPuppy = texture(texPuppy, vec2(Texcoord.x + sin(Texcoord.y * 25.0 + time * 2.0) / 70.0, Texcoord.y)) * vec4(0.7, 0.7, 1.0, 1.0);
        vec4 outKitten = texture(texKitten, vec2(Texcoord.x + sin(Texcoord.y * 25.0 + time * 2.0) / 70.0, Texcoord.y)) * vec4(0.7, 0.7, 1.0, 1.0);
        outColor = mix(outKitten, outPuppy, time);
    }

}
