#version 330 core

out vec4 FragColor; //最终输出的颜色

uniform vec3 cameraPos;

in vec3 FragPos;
in vec3 vertexNormal;

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

void main()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 normalDir = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuseRate = max(dot(lightDir, normalDir), 0.0);
	vec3 diffuse = diffuseRate * material.diffuse * light.diffuse;

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalDir);
	float specularRate = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularRate * material.specular * light.specular;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}