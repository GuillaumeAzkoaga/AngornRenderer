#version 400

in vec3 Position;
in vec3 Normal;
in vec2 TextureCoord;

layout (location = 0) out vec3 FragPosition;
layout (location = 1) out vec3 FragNormal;
layout (location = 2) out vec3 FragDiffuseColor;
layout (location = 3) out vec3 FragSpecularColor;
layout (location = 4) out vec3 FragAmbientColor;

struct Material
{
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};
uniform Material material;

void main()
{
	FragPosition = Position;
	FragNormal = normalize(Normal);	

	FragDiffuseColor = material.diffuse;
	FragSpecularColor = material.specular;	
	FragAmbientColor = material.ambient;
}