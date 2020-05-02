#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "Scene.h"
#include "ISystem.h"
#include <map>

class SceneManager : public ISystem {
public:
	static SceneManager* getInstance()
	{
		if (!instance_)
			instance_ = new SceneManager();
		return instance_;
	}

	void SetScene(std::string sceneFile);
	const Scene* getCurrentScene() const { return currentScene_; }

private:
	SceneManager() {}

	void Initialize() {}
	void Update(float dt = 0) {}
	void Shutdown() {}

	static SceneManager* instance_;

	Scene* currentScene_ = nullptr;
	std::map<std::string, Scene*> scenes_;
};
#endif