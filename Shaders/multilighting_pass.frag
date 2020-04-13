#version 400

in vec2 TextureCoord;

layout (location = 0) out vec3 FragLightning;

uniform sampler2D PositionTexture;
uniform sampler2D NormalTexture;
uniform sampler2D DiffuseColorTexture;
uniform sampler2D SpecularColorTexture;
uniform sampler2D AmbientColorTexture;

struct Light
{
	vec3 pos;
	vec3 color;
	float intensity;
};
uniform Light lights[1];
uniform int uLightAmount;

uniform vec3 viewPos;



vec3 PointLight(int i, vec3 pos, vec3 norm, vec3 diff, vec3 spec, vec3 amb)
{
	//Diffuse
	vec3 lightDir = normalize(lights[i].pos - pos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * diff * lights[i].color * lights[i].intensity;
	
	//Specular
	vec3 viewDir = normalize(viewPos - pos);
	vec3 halfwayDir = normalize(lightDir + viewDir);
	vec3 specular = lights[i].color * spec * pow(max(dot(norm, halfwayDir), 0.0), 32.0f) * lights[i].intensity;
	
	//Ambient
	vec3 ambient = lights[i].color * amb * lights[i].intensity;
	
	return diffuse + specular + ambient;
}

void main()
{
	vec3 pos = vec3(texture(PositionTexture, TextureCoord));
	vec3 norm = vec3(texture(NormalTexture, TextureCoord));
	vec3 diff = vec3(texture(DiffuseColorTexture, TextureCoord));
	vec3 spec = vec3(texture(SpecularColorTexture, TextureCoord));
	vec3 ambient = vec3(texture(AmbientColorTexture, TextureCoord));
	
	FragLightning = vec3(0,0,0);
	
	for ( int count = 0; count < uLightAmount; ++count)
	{
		FragLightning += PointLight(count, pos, norm, diff, spec, ambient);
	}
}