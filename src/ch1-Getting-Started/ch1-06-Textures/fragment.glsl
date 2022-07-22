#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform vec4 globalColor; // ��OpenGL����������趨�������
uniform sampler2D globalTexture;

void main()
{
   FragColor = texture(globalTexture, texCoord);
}