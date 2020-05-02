#ifndef SCENE_H_
#define SCENE_H_

#include "CustomObject.h"
#include "Ball.h"
#include "Light.h"

class Scene 
{
public:
	Scene() {
		CreateScene();
	}

	const std::vector<Light*> getLights() const { return lights_; }

private:
	
	void CreateScene();

	Ball* test;
	std::vector<Light*> lights_;
	std::vector<IRenderable*> objects_;
};
#endif
