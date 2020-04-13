#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTextureCoord;

out vec3 Position;
out vec3 Normal;
out vec2 TextureCoord;

uniform mat4 ModelViewMatrix;

void main()
{
	Position = vec3( ModelViewMatrix * vec4(VertexPosition,1.0) );
	Normal = normalize((ModelViewMatrix * vec4(VertexNormal, 0.0)).xyz);  
	//TextureCoord = VertexTextureCoord;
	TextureCoord.x = VertexTextureCoord.x;
	TextureCoord.y = 1-VertexTextureCoord.y;
}