#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "RenderingUtils.h"
#include <string>

class TextureChannel
{
public:
	TextureChannel(std::string textureFile);

	const GLuint getTexture() const { return textureID_; }

private:
	void LoadTexture();
	GLuint textureID_;

	std::string textureFileName_;
};

//TODO: Load pink texture if none is given (textureDiffuse = "" in constructor)
class Texture
{
public:
	Texture(std::string textureName, std::string textureDiffuse = "", std::string textureSpecular = "", std::string textureAmbient = "");

	GLuint getDiffuseTexture() const { return diffuse_->getTexture(); }
	GLuint getSpecularTexture() const { return specular_->getTexture(); }
	GLuint getAmbientTexture() const { return ambient_->getTexture(); }

	const std::string getName() const { return textureName_; }

private:
	TextureChannel* diffuse_;
	TextureChannel* specular_;
	TextureChannel* ambient_;

	std::string textureName_;
};



#endif