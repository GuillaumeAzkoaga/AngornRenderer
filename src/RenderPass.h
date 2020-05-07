#ifndef RENDER_PASS_H_
#define RENDER_PASS_H_

#include "IRenderPass.h"
#include "GBuffer.h"

class RenderPass : public IRenderPass
{
public:
	RenderPass();
	void Apply();


};

#endif