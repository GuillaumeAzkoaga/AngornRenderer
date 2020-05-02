#ifndef RESOURCE_LOADER_H_
#define RESOURCE_LOADER_H_

#include "ISystem.h"
#include "Mesh.h"
#include "Material.h"

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

private:
	ResourceLoader() {};
	static ResourceLoader* instance_;

	std::vector<Mesh*> meshes_;
	std::vector<Material*> materials_;
};

#endif