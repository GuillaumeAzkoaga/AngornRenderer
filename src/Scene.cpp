#include "Scene.h"
#include "Camera.h"
#include "RenderView.h"
#include "Renderer.h"

#include "json/json.h"

#include <fstream>



void Scene::LoadSceneFromJson(std::string jsonFile)
{	
	try
	{
		std::ifstream scene(jsonFile, std::ifstream::binary);
		Json::Value root;   // starts as "null"; will contain the root value after parsing
		scene >> root;

		//Load Camera
		const Json::Value camera = root["Camera"];
		if (camera.size() == 0)
		{
			Camera::getInstance()->CreateCamera();
		}
		else {
			glm::vec3 position = glm::vec3(camera["position"].get("x", 0.f).asFloat(), camera["position"].get("y", 0.f).asFloat(), camera["position"].get("z", 0.f).asFloat());
			Camera::getInstance()->CreateCamera(position);
		}
		

		//Load objects
		const Json::Value objects = root["Objects"];
		for (unsigned i = 0; i < objects.size(); ++i)
		{
			Mesh* mesh = ResourceLoader::getInstance()->getMesh(objects[i].get("mesh", "../Data/Meshes/sphere_8_4.obj").asString());

			Material* material = ResourceLoader::getInstance()->getMaterial(static_cast<MATERIAL_TYPE>(objects[i].get("material", 0).asUInt()));

			glm::vec3 position = glm::vec3(objects[i]["position"].get("x", 0.0f).asFloat(), objects[i]["position"].get("y", 0.0f).asFloat(), objects[i]["position"].get("z", 0.0f).asFloat());

			glm::vec3 scale = glm::vec3(objects[i]["scale"].get("x", 0.0f).asFloat(), objects[i]["scale"].get("y", 0.0f).asFloat(), objects[i]["scale"].get("z", 0.0f).asFloat());

			float angle = objects[i]["rotation"].get("angle", 0.0f).asFloat();
			glm::vec3 axisAngle = glm::vec3(objects[i]["rotation"]["axis"].get("x", 0.0f).asFloat(), objects[i]["rotation"]["axis"].get("y", 0.0f).asFloat(), objects[i]["rotation"]["axis"].get("z", 0.0f).asFloat());
			glm::quat rotation = glm::angleAxis(angle, axisAngle);

			objects_.push_back(new CustomObject(position, scale, rotation, mesh, material));
		}

		for (IRenderable* obj : objects_)
			obj->GenerateAndBindBuffers();

		//Load Lights
		const Json::Value lights = root["Lights"];
		if (lights.size() == 0)
		{
			lights_.push_back(new Light());
		}
		else {
			for (unsigned i = 0; i < lights.size(); ++i)
			{
				glm::vec3 position = glm::vec3(lights[i]["position"].get("x", 0.f).asFloat(), lights[i]["position"].get("y", 0.f).asFloat(), lights[i]["position"].get("z", 0.f).asFloat());
				glm::vec3 color = glm::vec3(lights[i]["color"].get("r", 1.f).asFloat(), lights[i]["color"].get("g", 1.f).asFloat(), lights[i]["color"].get("b", 1.f).asFloat());
				lights_.push_back(new Light(position, color));
			}			
		}

		name_ = jsonFile;
	}
	catch (std::exception& e)
	{
		MessageBox(RenderView::getInstance()->getHandle(), ("Could not load scene from " + std::string(jsonFile) + e.what()).c_str(), "Scene import error", MB_ICONERROR);
	}
	
}


void Scene::ReloadCamera() const
{
	try {
		std::ifstream scene(name_, std::ifstream::binary);
		Json::Value root;   // starts as "null"; will contain the root value after parsing
		scene >> root;

		//Load Camera
		const Json::Value camera = root["Camera"];
		if (camera.size() == 0)
		{
			Camera::getInstance()->CreateCamera();
		}
		else {
			glm::vec3 position = glm::vec3(camera["position"].get("x", 0.f).asFloat(), camera["position"].get("y", 0.f).asFloat(), camera["position"].get("z", 0.f).asFloat());
			Camera::getInstance()->CreateCamera(position);
		}
	}
	catch (std::exception& e)
	{
		MessageBox(RenderView::getInstance()->getHandle(), ("Could not load scene from " + name_ + e.what()).c_str(), "Scene import error", MB_ICONERROR);
	}

	
}
