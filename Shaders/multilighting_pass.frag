#version 400

in vec2 TexCoord0;

layout (location = 0) out vec3 MultiLightingOut;


struct Light
{
	vec3 pos;
	vec3 color;
	float intensity;
};
uniform Light lights[10];
uniform int uLightAmount;

uniform vec3 viewPos;

uniform sampler2D PosBuffer;
uniform sampler2D DiffBuffer;
uniform sampler2D NormBuffer;
uniform sampler2D SpecularTex;
uniform sampler2D AmbientTex;

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
	vec3 pos = vec3(texture(PosBuffer, TexCoord0));
	vec3 norm = vec3(texture(NormBuffer, TexCoord0));
	vec3 diff = vec3(texture(DiffBuffer, TexCoord0));
	vec3 spec = vec3(texture(SpecularTex, TexCoord0));
	vec3 ambient = vec3(texture(AmbientTex, TexCoord0));
	
	MultiLightingOut = vec3(0,0,0);
	
	for ( int count = 0; count < uLightAmount; ++count)
	{
		MultiLightingOut += PointLight(count, pos, norm, diff, spec, ambient);
	}
}