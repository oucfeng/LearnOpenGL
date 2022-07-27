#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 vertexNormal;
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0)); //世界空间
	//vertexNormal = aNormal; //本地模型空间
	vertexNormal = mat3(transpose(inverse(model))) * aNormal;
	texCoord = aTexCoords;
}