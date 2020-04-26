#ifndef RESOURCE_LOADER_H_
#define RESOURCE_LOADER_H_

#include "ISystem.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

class ResourceLoader  : public ISystem
{
public:
	static ResourceLoader* getInstance()
	{
		if (!instance_)
			instance_ = new ResourceLoader();

		return instance_;
	}

	void Initialize() {};
	void Update(float dt = 0) {};
	void Shutdown() {};

	/// <summary>
	/// Checks if the mesh was already loaded. Loads it if needed
	/// </summary>
	/// <param name="fileName">The file containing mesh data</param>
	/// <returns>Pointer to the loaded mesh</returns>
	Mesh* getMesh(const std::string fileName) ;

	/// <summary>
	/// Checks if the Material was already loaded. Loads it if needed
	/// </summary>
	/// <param name="type">The type of material to load</param>
	/// <returns>Pointer to the loaded material</returns>
	Material* getMaterial(const MATERIAL_TYPE type) ;

	/// <summary>
	/// Checks if the Texture was already loaded. Loads it if needed
	/// </summary>
	/// <param name="textureName">The name under which the texture was saved (not the actual file path)</param>
	/// <param name="textureDiffuse">File path for diffuse texture (if none is given, use default texture)</param>
	/// <param name="textureSpecular">File path for specular texture (if none is given, use diffuse texture)</param>
	/// <param name="textureAmbient">File path for ambient texture (if none is given, use diffuse texture)</param>
	/// <returns>Pointer to the loaded texture</returns>
	Texture* getTexture(const std::string textureName, std::string textureDiffuse = "", std::string textureSpecular = "", std::string textureAmbient = "");

private:
	ResourceLoader() {};
	static ResourceLoader* instance_;

	std::vector<Mesh*> meshes_;
	std::vector<Material*> materials_;
	std::vector<Texture*> textures_;
};

#endif