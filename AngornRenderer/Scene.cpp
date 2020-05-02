#include "Scene.h"
#include "Camera.h"

void Scene::CreateScene()
{
	Camera::getInstance()->CreateCamera(glm::vec3(-1000.f, 0.0f, 0.0f));

	objects_.push_back(new Ball(glm::vec3(0, 0, 0), glm::vec3(200), glm::angleAxis(0.0f, glm::vec3(1, 0, 0)), ResourceLoader::getInstance()->getMaterial(MATERIAL_TYPE::MAT_RUBY)));
	objects_.push_back(new CustomObject(glm::vec3(500, 0, 0), glm::vec3(50), glm::angleAxis(30.f, glm::vec3(0, 1, 0)), ResourceLoader::getInstance()->getMesh("../Meshes/Luma.obj"), ResourceLoader::getInstance()->getMaterial(MATERIAL_TYPE::MAT_CHROME)));

	for (IRenderable* obj : objects_)
		obj->GenerateAndBindBuffers();

	lights_.push_back(new Light(glm::vec3(0, 500, 0), glm::vec3(1)));
}
