#ifndef LIGHT_PASS_H_
#define LIGHT_PASS_H_
#include "IRenderPass.h"
#include "GBuffer.h"

class LightPass : public IRenderPass
{
public:
	LightPass();

	void Apply();

	enum TexturesOut
	{
		LightingOut,
		NUM_TEXTURES
	};

private:
	GBuffer* lightBuffer_ = nullptr;
};

#endif
