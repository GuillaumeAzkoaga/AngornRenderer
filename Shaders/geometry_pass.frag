#version 400

in vec3 Normal;
in vec3 Position;
in vec2 UV;      

layout (location = 0) out vec3 FragPosition;
layout (location = 1) out vec3 FragNormal;
layout (location = 2) out vec3 FragDiffuseColor;
layout (location = 3) out vec3 FragSpecularColor;
layout (location = 4) out vec3 FragAmbientColor;

uniform int hasTextures; 
uniform sampler2D textureDiffuse;   
uniform sampler2D textureSpecular;   
uniform sampler2D textureAmbient; 

uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform vec3 materialAmbient;

void main()
{
	FragPosition = Position;
	FragNormal = normalize(Normal);	
	
	if(hasTextures == 0)
	{
		FragDiffuseColor = materialDiffuse;
		FragSpecularColor = materialSpecular;	
		FragAmbientColor = materialAmbient;
	}
	else
	{
		FragDiffuseColor = texture(textureDiffuse, UV).xyz;
		FragSpecularColor = texture(textureSpecular, UV).xyz;
		FragAmbientColor = texture(textureAmbient, UV).xyz;
	}
}