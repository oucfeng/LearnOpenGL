#version 330 core

out vec4 FragColor;
in vec4 vertexColor;

uniform vec4 globalColor; // 在OpenGL程序代码中设定这个变量

void main()
{
   FragColor = vertexColor;
}