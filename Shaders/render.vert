#version 400

layout (location = 0) in vec3 Position;
layout (location = 2) in vec2 TexCoord;

out vec2 VertexTextureCoord;

void main()
{
  VertexTextureCoord = TexCoord;
  gl_Position = vec4(Position,1.0);
}