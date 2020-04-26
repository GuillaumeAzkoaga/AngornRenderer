#include "Texture.h"
#include "RenderView.h"
#include "stb_image.h"

#include <fstream>

Texture::Texture(std::string textureName, std::string textureDiffuse, std::string textureSpecular, std::string textureAmbient) : textureName_(textureName)
{
	std::string defaultTexture = textureDiffuse.empty() ? "TEMP_PINK.PNG" : textureDiffuse;
	diffuse_ = new TextureChannel(defaultTexture);
	specular_ = new TextureChannel(textureSpecular.empty() ? defaultTexture : textureSpecular);
	ambient_ = new TextureChannel(textureAmbient.empty() ? defaultTexture : textureAmbient);
}

TextureChannel::TextureChannel(std::string textureFile) : textureFileName_(textureFile)
{
	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(textureFileName_.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		MessageBox(RenderView::getInstance()->getHandle(), ("Failed to load texture from file " + textureFileName_ + ".").c_str(), "Texture Load Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
	}
	stbi_image_free(data);
}

void TextureChannel::LoadTexture()
{
	

	
}
