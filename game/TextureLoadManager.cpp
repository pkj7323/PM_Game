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

GLuint TextureLoadManager::GetTexture(const string& name)
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

void TextureLoadManager::Use(const string& name, GLuint index)
{
	if (m_texture.find(name) != m_texture.end())
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_texture[name]);
	}
	else
	{
		std::cout << "Failed to find texture" << std::endl;
	}
}

void TextureLoadManager::loadCubeMap(const string& name,vector<string> faces)
{
	GLuint ID;
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	int width, height, nrChannels;
	for (size_t i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			cout << "Cubemap texture failed to load at path: " << faces[i] << endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	m_texture[name] = ID;
}
