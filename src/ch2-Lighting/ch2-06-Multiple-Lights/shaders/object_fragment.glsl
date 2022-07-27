#version 330 core

out vec4 FragColor; //最终输出的颜色

uniform vec3 cameraPos;

in vec3 FragPos;
in vec3 vertexNormal;
in vec2 texCoord;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
	vec3 position;

	float constant;
    float linear;
    float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

struct SpotLight {
	vec3 position;
	vec3 direction;

	float cutoff;
	float outercutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform SpotLight spotLight;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};
uniform Material material;

vec3 CalDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 color;
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

	vec3 normalDir = normalize(vertexNormal);
	vec3 lightDir = normalize(-light.direction);
	float diffuseRate = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diffuseRate * light.diffuse * vec3(texture(material.diffuse, texCoord));

	vec3 reflectDir = reflect(-lightDir, normalDir);
	float specularRate = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularRate * light.specular * vec3(texture(material.specular, texCoord));

	color = ambient + diffuse + specular;
	return color;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 color;

	vec3 lightDir = normalize(light.position - fragPos);
	float lightDistance = distance(light.position, fragPos);

	vec3 ambient = dirLight.ambient * vec3(texture(material.diffuse, texCoord));

	vec3 normalDir = normalize(vertexNormal);
	float diffuseRate = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diffuseRate * light.diffuse * vec3(texture(material.diffuse, texCoord));

	vec3 reflectDir = reflect(-lightDir, normalDir);
	float specularRate = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularRate * light.specular * vec3(texture(material.specular, texCoord));

	color = ambient + diffuse + specular;

	float attenuation = 1.0 / (light.constant + light.linear * lightDistance + 
                light.quadratic * (lightDistance * lightDistance));
	color *= attenuation;
	return color;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 color;

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

	vec3 normalDir = normalize(vertexNormal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diffuseRate = max(dot(lightDir, normalDir), 0.0);
	vec3 diffuse = diffuseRate * light.diffuse * vec3(texture(material.diffuse, texCoord));

	vec3 reflectDir = reflect(-lightDir, normalDir);
	float specularRate = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = specularRate * light.specular * vec3(texture(material.specular, texCoord));

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutoff - light.outercutoff;
	float intensity = clamp((theta - light.outercutoff) / epsilon, 0.0, 1.0);

	color = ambient + (diffuse + specular) * intensity;

	return color;
}

void main()
{
	// common values
	vec3 normalDir = normalize(vertexNormal);
	vec3 viewDir = normalize(cameraPos - FragPos);

	vec3 color;
	// directional light
	color += CalDirLight(dirLight, normalDir, viewDir);

	// point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		color += CalcPointLight(pointLights[i], normalDir, FragPos, viewDir);

	// spotLight
	color += CalcSpotLight(spotLight, normalDir, FragPos, viewDir);
	
	FragColor = vec4(color, 1.0);
}