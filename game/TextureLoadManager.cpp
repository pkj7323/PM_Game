#include "stdafx.h"
#include "TextureLoadManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureLoadManager::TextureLoadManager()
{
	
}

TextureLoadManager::~TextureLoadManager()
{
	
}

void TextureLoadManager::Load(const string& name,const string& filename)
{
	if (m_texture.find(name) != m_texture.end())
	{
		return;
	}
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		m_texture[name] = textureID;

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}
	

}

GLuint TextureLoadManager::Use(const string& name)
{
	if (m_texture.find(name) != m_texture.end())
	{
		auto texture = m_texture[name];
		return texture;
		
	}
	else
	{
		std::cout << "Failed to find texture" << std::endl;
	}
}
