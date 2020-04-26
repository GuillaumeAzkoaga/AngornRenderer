#include "ResourceLoader.h"

ResourceLoader* ResourceLoader::instance_ = 0;

Mesh* ResourceLoader::getMesh(const std::string fileName)
{
	for (Mesh* mesh : meshes_)
	{
		if (mesh->getName() == fileName) 
			return mesh;
	}
	
	Mesh* mesh = new Mesh();
	mesh->LoadMesh(fileName);
	meshes_.push_back(mesh);
	return mesh;
}
Material* ResourceLoader::getMaterial(const MATERIAL_TYPE type) 
{
	for (Material* material : materials_)
	{
		if (material->getType() == type)
			return material;
	}

	Material* material = new Material(type);
	materials_.push_back(material);
	return material;
}

Texture* ResourceLoader::getTexture(const std::string textureName, std::string textureDiffuse, std::string textureSpecular, std::string textureAmbient)
{
	for (Texture* texture : textures_)
	{
		if (texture->getName() == textureName)
			return texture;
	}

	Texture* texture = new Texture(textureName, textureDiffuse, textureSpecular, textureAmbient);
	textures_.push_back(texture);
	return texture;
}
