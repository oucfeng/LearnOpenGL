#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;

vec2 offsets[9] = vec2[](
	vec2(-offset,  offset), // ����
    vec2( 0.0f,    offset), // ����
    vec2( offset,  offset), // ����
    vec2(-offset,  0.0f),   // ��
    vec2( 0.0f,    0.0f),   // ��
    vec2( offset,  0.0f),   // ��
    vec2(-offset, -offset), // ����
    vec2( 0.0f,   -offset), // ����
    vec2( offset, -offset)  // ����
);

float kernal[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
);

void main()
{
	vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords + offsets[i]));
    }

    vec3 color = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        color += sampleTex[i] * kernal[i];
    }

    FragColor = vec4(color, 1.0f);
}