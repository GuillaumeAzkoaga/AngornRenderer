#include "Texture.h"
#include "RenderView.h"

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
	LoadTexture();
}

void TextureChannel::LoadTexture()
{
	std::ifstream is(textureFileName_.c_str(), std::ifstream::binary);
	if (is)
	{
		// get length of file:
		is.seekg(0, is.end);
		unsigned int length = int(is.tellg());
		is.seekg(0, is.beg);


		char* imgBuffer = new char[length];
		// read data as a block:
		is.read(imgBuffer, length);

		if (!is)
		{
			MessageBox(RenderView::getInstance()->getHandle(), ("Failed to load texture from file " + textureFileName_ + ".").c_str(), "Texture Load Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
			is.close();
			
		}
		else
		{
			is.close();
			//textureID_ = SOIL_load_OGL_texture_from_memory((unsigned char*)imgBuffer, length * sizeof(char), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT);		
			//textureID_ = SOIL_load_OGL_texture(textureFileName_.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);

			// Check if the texture was loaded correctly
			if (textureID_ == 0)
				MessageBox(RenderView::getInstance()->getHandle(), ("Failed to load texture from file " + textureFileName_ + ".").c_str(), "Texture Load Error", MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
			else
			{
				// "Bind" the newly created texture : all future texture functions will modify this texture
				glBindTexture(GL_TEXTURE_2D, textureID_);

				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			}
		}
		

		

		

	}
		
	

}
