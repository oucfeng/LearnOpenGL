#version 330 core

out vec4 FragColor;

uniform vec3 lightColor; // 在OpenGL程序代码中设定这个变量
uniform vec3 objectColor;

void main()
{
   FragColor = vec4(lightColor * objectColor, 1.0);
}