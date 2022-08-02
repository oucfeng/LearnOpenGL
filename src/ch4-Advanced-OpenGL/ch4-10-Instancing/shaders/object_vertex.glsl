#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;

out VS_OUT {
    vec3 color;
} vs_out;

uniform vec2 offset[100];

void main()
{
    gl_Position = vec4(aPos + offset[gl_InstanceID], 0.0, 1.0);
    vs_out.color = aColor;
}