#version 400

in vec3 Normal0;
in vec3 WorldPos0;
in vec2 UV;      
in vec3 TessDepth;



layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec3 DiffuseOut;
layout (location = 2) out vec3 NormalOut;
layout (location = 3) out vec3 SpecOut;
layout (location = 4) out vec3 AmientTexOut;
layout (location = 5) out vec3 DepthTessOut;

uniform sampler2D TexD;   
uniform sampler2D TexS;   
uniform sampler2D TexA;  
uniform int hasTextures; 
uniform int isLight;
uniform vec3 color;

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

	if(isLight == 1)
	{
		DiffuseOut = color;
		SpecOut = color;		
		AmientTexOut = color;
	}
	else
	{
		if(hasTextures == 0)
		{
			DiffuseOut = material.diffuse;
			SpecOut = material.specular;	
			AmientTexOut = material.ambient;
		}
		else
		{
			DiffuseOut = texture(TexD, UV).xyz;
			SpecOut = texture(TexS, UV).xyz;		
			AmientTexOut = texture(TexA, UV).xyz;	
		}
	
	}
	

}