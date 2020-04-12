#version 420

in vec3 Normal0;
in vec3 WorldPos0;


layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 SpecularColorOut;
layout (location = 4) out vec3 AmbientColorOut;

struct Material
{
	vec3 diffuse;
	vec3 specular;
	vec3 ambient;
};
uniform Material material;

void main()
{
	WorldPosOut = WorldPos0;
	NormalOut = normalize(Normal0);	

	DiffuseOut = material.diffuse;
	SpecularColorOut = material.specular;	
	AmbientColorOut = material.ambient;
}