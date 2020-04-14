#version 400

in vec2 TextureCoord;

uniform sampler2D TextureToRender;

out vec4 FragColor;

void main()
{
	FragColor = vec4(texture(TextureToRender, TextureCoord).rgb, 1.0);
}