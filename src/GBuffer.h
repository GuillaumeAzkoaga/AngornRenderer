#ifndef GBUFFER_H_
#define GBUFFER_H_

#include "RenderingUtils.h"

#include <vector>

class GBuffer
{
public:
	GBuffer() {}
	~GBuffer() {}
	
	void Initialize(const unsigned int windowWidth, const unsigned int windowHeight, const unsigned textureAmount, const bool useDepth = true);

	void BindFrameBuffer() const;

	const std::vector<GLuint> getTexturesList() { return textureList_; }

private:
	bool isUsingDepth_ = false;
	GLuint frameBufferOject_ = 0;	
	GLuint depthTexture_ = 0;
	std::vector<GLuint> textureList_;
};
#endif
