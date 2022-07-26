#version 330 core

out vec4 FragColor;

uniform vec3 lightColor; // 在OpenGL程序代码中设定这个变量
uniform vec3 objectColor;

uniform vec3 lightPos;
uniform vec3 cameraPos;

in vec3 FragPos;
in vec3 vertexNormal;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 normalDir = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diffuseRate = max(dot(lightDir, normalDir), 0.0);
	vec3 diffuse = lightColor * diffuseRate;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalDir);
	float specularRate = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = lightColor * specularRate * specularStrength;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4(result, 1.0);
}