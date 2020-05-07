#ifndef OUTPUT_RENDERABLE_H_
#define OUTPUT_RENDERABLE_H_

#include "IRenderable.h"
#include "ResourceLoader.h"

class OutputRenderable : public IRenderable
{
public:
	OutputRenderable() : IRenderable(false)
	{
		mesh_ =  ResourceLoader::getInstance()->getMesh("../Data/Meshes/plane.obj");
		GenerateAndBindBuffers();
	}
};

#endif