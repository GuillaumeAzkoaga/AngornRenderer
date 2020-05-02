#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTextureCoords;


out vec3 Position;
out vec3 Normal;
out vec2 TextureCoord;


uniform mat4 model;
uniform mat4 view;

void main()
{
	Position = vec3( (view*model) * vec4(VertexPosition,1.0) );
	Normal = normalize(((view*model) * vec4(VertexNormal, 0.0)).xyz);  
	TextureCoord.x = VertexTextureCoords.x;
	TextureCoord.y = 1-VertexTextureCoords.y;
}