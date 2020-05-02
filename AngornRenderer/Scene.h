#ifndef SCENE_H_
#define SCENE_H_

#include "CustomObject.h"
#include "Ball.h"
#include "Light.h"
#include "Renderer.h"
//TODO export current scene to json

class Scene 
{
public:
	Scene(std::string jsonFile) {
		LoadSceneFromJson(jsonFile);
	}

	const std::vector<Light*> getLights() const { return lights_; }

	const void UnregisterRenderables() {
		for (IRenderable* obj : objects_)
			Renderer::getInstance()->UnregisterRenderable(obj);
	}
	const void RegisterRenderables() {
		for (IRenderable* obj : objects_)
			Renderer::getInstance()->RegisterRenderable(obj);
	}
	void ReloadCamera() const;
private:	
	void LoadSceneFromJson(std::string jsonFile);
	std::vector<Light*> lights_;
	std::vector<IRenderable*> objects_;

	std::string name_;
};
#endif
