#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec2 texCoord;

uniform vec4 globalColor; // 在OpenGL程序代码中设定这个变量
uniform sampler2D globalTexture;

void main()
{
   FragColor = texture(globalTexture, texCoord);
}