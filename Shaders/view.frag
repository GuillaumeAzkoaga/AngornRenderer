#version 400

in vec2 TexCoord0;

float NearPlane = 1.0;
float FarPlane = 5000.0;

uniform sampler2D Texture2Show;
uniform int isDepth;

out vec4 FragColor;


vec3 linearize(vec3 val)
{
	float linearized = (2.0 * NearPlane) / (FarPlane + NearPlane - val.r * (FarPlane - NearPlane));
	return vec3(linearized, linearized, linearized);
}

vec4 ShowDepth()
{
	return vec4(linearize(texture(Texture2Show, TexCoord0).rgb),1.0);
}

vec4 ShowTexture()
{
	return vec4(texture(Texture2Show, TexCoord0).rgb, 1.0);
}

void main()
{
	if(isDepth == 1)
		FragColor = ShowDepth();
	else
		FragColor = ShowTexture();
}