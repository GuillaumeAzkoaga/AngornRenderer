#version 420

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Normal;

out vec3 Normal0;
out vec3 WorldPos0;

uniform mat4 MV;

void main()
{
	WorldPos0 = vec3( MV * vec4(Position,1.0) );
	Normal0 = normalize((MV * vec4(Normal, 0.0)).xyz);  
}