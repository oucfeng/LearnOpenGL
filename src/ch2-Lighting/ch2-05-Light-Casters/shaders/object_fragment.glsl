#version 330 core

out vec4 FragColor; //最终输出的颜色

uniform vec3 cameraPos;

in vec3 FragPos;
in vec3 vertexNormal;
in vec2 texCoord;

struct Light {
	vec3 position;
	vec3 direction;
	float cutoff;
	float outercutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

	vec3 normalDir = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diffuseRate = max(dot(lightDir, normalDir), 0.0);
	vec3 diffuse = diffuseRate * light.diffuse * vec3(texture(material.diffuse, texCoord));

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, normalDir);
	float specularRate = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularRate * light.specular * vec3(texture(material.specular, texCoord));

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutoff - light.outercutoff;
	float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0, 1.0);

	vec3 color = ambient + (diffuse + specular) * intensity;
	FragColor = vec4(color, 1.0);
}