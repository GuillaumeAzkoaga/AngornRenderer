#ifndef GEOMETRY_PASS_H_
#define GEOMETRY_PASS_H_
#include "IRenderPass.h"
#include "GBuffer.h"

class GeometryPass : public IRenderPass
{
public:
	GeometryPass();

	void Apply();

private:
	enum Textures
	{
		Position,
		Diffuse,
		Normal,
		Specular,
		AmbientColor,
		MAX_TEXTURES
	};
	GBuffer* gBuffer_;
};

#endif