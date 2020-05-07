#version 400

in vec2 TexCoord0;

uniform sampler2D NormBuffer;
uniform sampler2D DepthBuffer;


float DepthThreshold = 0.005;
float NormalThreshold = 0.005;
int Width = 1280;
int Height = 720;

layout( location = 0 ) out vec4 EdgesOut;

	// Linearizes Depth
	float LDepth( vec3 color ) {
	float z = color.x;
	float n = 1.0;
	float f = 1000.0;
	float c = (2.0 * n) / (f + n - z * (f - n));

	return c;
}

vec4 ComputeEdges(sampler2D RenderTex, float TH)
{
	float dx = 1.0 / float(Width);
	float dy = 1.0 / float(Height);
	float s00 = LDepth(texture( RenderTex, TexCoord0 + vec2(-dx,dy) ).rgb);
	float s10 = LDepth(texture( RenderTex, TexCoord0 + vec2(-dx,0.0) ).rgb);
	float s20 = LDepth(texture( RenderTex, TexCoord0 + vec2(-dx,-dy) ).rgb);
	float s01 = LDepth(texture( RenderTex, TexCoord0 + vec2(0.0,dy) ).rgb);
	float s21 = LDepth(texture( RenderTex, TexCoord0 + vec2(0.0,-dy) ).rgb);
	float s02 = LDepth(texture( RenderTex, TexCoord0 + vec2(dx, dy) ).rgb);
	float s12 = LDepth(texture( RenderTex, TexCoord0 + vec2(dx, 0.0) ).rgb);
	float s22 = LDepth(texture( RenderTex, TexCoord0 + vec2(dx, -dy) ).rgb);
	float sx = s00 + 2 * s10 + s20 - (s02 + 2 * s12 + s22);
	float sy = s00 + 2 * s01 + s02 - (s20 + 2 * s21 + s22);
	float dist = sx * sx + sy * sy;
	if( dist>TH )
		return vec4(1.0);
	else
		return vec4(0.0,0.0,0.0,1.0);
}
void main()
{
	EdgesOut = ComputeEdges(NormBuffer, NormalThreshold) + ComputeEdges(DepthBuffer, DepthThreshold);
	//EdgesOut = ComputeEdges(NormBuffer, NormalThreshold);
	//EdgesOut =  ComputeEdges(DepthBuffer, DepthThreshold);
}