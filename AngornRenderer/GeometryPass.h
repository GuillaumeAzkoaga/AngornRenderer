#ifndef GEOMETRY_PASS_H_
#define GEOMETRY_PASS_H_
#include "IRenderPass.h"
#include "GBuffer.h"

class GeometryPass : public IRenderPass
{
public:
	GeometryPass();

	void Apply();

	enum TexturesOut
	{
		Position,
		Normal,
		DiffuseColor,
		SpecularColor,
		AmbientColor,
		NUM_TEXTURES
	};

private:	
	GBuffer* gBuffer_ = nullptr;
};

#endif