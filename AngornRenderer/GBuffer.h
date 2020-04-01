#ifndef GBUFFER_H_
#define GBUFFER_H_

#include "RenderingUtils.h"

#include <vector>

//TODO: Make so that the depthTexture is always the last one so textureList_[textureAmount-1]

class GBuffer
{
public:
	GBuffer() {}
	~GBuffer() {}
	
	void Initialize(const unsigned int windowWidth, const unsigned int windowHeight, const unsigned textureAmount, const bool useDepth = true);

	void BindFrameBuffer() const;

private:

	bool isUsingDepth_;
	GLuint frameBufferOject_;
	std::vector<GLuint> textureList_;
	GLuint depthTexture_;
};
#endif
