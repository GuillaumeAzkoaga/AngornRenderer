#include "SceneManager.h"
#include "Renderer.h"

SceneManager* SceneManager::instance_ = 0;


void SceneManager::SetScene(std::string jsonFile)
{
	if (currentScene_)	
		currentScene_->UnregisterRenderables();	

	
	std::map<std::string, Scene*>::iterator loc = scenes_.find(jsonFile);
	if (loc == scenes_.cend())
	{
		//If hasn't be loaded yet, load the data from the json file and change the current displayed scene
		currentScene_ = new Scene(jsonFile);
		scenes_.insert(std::pair<std::string, Scene*>(jsonFile, currentScene_));
	}
	else
	{
		//it was already loaded so we can simply switch to the new one
		currentScene_ = scenes_.at(jsonFile);
		currentScene_->ReloadCamera();
		currentScene_->RegisterRenderables();
	}		
}

