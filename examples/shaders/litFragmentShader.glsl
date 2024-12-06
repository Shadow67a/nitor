#version 460 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 fragNormal;
in vec2 texCoord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
}; 

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));

	vec3 normal = normalize(fragNormal);
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 viewDir = normalize(viewPos-fragPos);

	float diff = max(dot(normal, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));

	vec3 reflectDir = reflect(lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

	vec3 result = (ambient + diffuse + specular);


	FragColor = vec4(result, 1.0f);
} 
