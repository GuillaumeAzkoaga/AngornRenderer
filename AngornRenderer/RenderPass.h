#ifndef RENDER_PASS_H_
#define RENDER_PASS_H_

#include "ShaderProgram.h"
#include "ISystem.h"

class RenderPass : public ISystem
{
public:

protected:
	ShaderProgram* program_;

};

#endif