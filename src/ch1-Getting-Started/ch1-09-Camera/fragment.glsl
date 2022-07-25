#version 330 core

out vec4 FragColor;

in vec2 texCoord;

uniform vec4 globalColor; // 在OpenGL程序代码中设定这个变量
uniform sampler2D globalTexture1;
uniform sampler2D globalTexture2;

void main()
{
   FragColor = mix(texture(globalTexture1, texCoord), texture(globalTexture2, texCoord), 0.2);
}