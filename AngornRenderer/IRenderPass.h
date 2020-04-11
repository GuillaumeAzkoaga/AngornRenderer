#ifndef RENDER_PASS_H_
#define RENDER_PASS_H_

#include "ShaderProgram.h"

class IRenderPass 
{
public:
	virtual void Apply() = 0;

protected:
	ShaderProgram* program_ = nullptr;

};

#endif