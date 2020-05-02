#ifndef SCENE_H_
#define SCENE_H_

#include "CustomObject.h"
#include "Ball.h"
#include "Light.h"

class Scene 
{
public:
	Scene() {
		LoadSceneFromJson();
	}

	Scene(std::string sceneJson) {
		LoadSceneFromJson(sceneJson);
	}

	const std::vector<Light*> getLights() const { return lights_; }

	void ChangeScene(std::string sceneJson);
private:	
	void LoadSceneFromJson(std::string jsonFile = "../Data/Scenes/Default.json");
	std::vector<Light*> lights_;
	std::vector<IRenderable*> objects_;

	std::string currentScene = "";
	std::string previousScene = "";
};
#endif
