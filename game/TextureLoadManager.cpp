#include "stdafx.h"
#include "TextureLoadManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



void TextureLoadManager::Init()
{
	cout << "텍스쳐 로드" << endl;
	Load("wall", "wall.jpg");
	Load("container2", "container2.png");
	Load("container2_specular", "container2_specular.png");
	Load("marble", "resources/marble.jpg");
	Load("metal", "resources/metal.png");
	Load("space_ship", "resources/space_ship_test_color.png");
	vector<std::string> faces
	{
		"resources/right.jpg",
		"resources/left.jpg",
		"resources/top.jpg",
		"resources/bottom.jpg",
		"resources/front.jpg",
		"resources/back.jpg"
	};
	loadCubeMap("skybox", faces);//스카이박스 텍스쳐 로드
	//스카이박스는 로드가 다르다. 큐브맵함수들을 사용해서 로드하고 여러장의 사진 필요하기 에 faces벡터배열을 넘겨준다.
	cout << "텍스쳐 로드 종료" << endl;
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

		std::cout<< name << ": Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}
	

}

void TextureLoadManager::Release()
{

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
		std::cout << name << ": ";
		std::cout << "Failed to find texture" << std::endl;
		return -1;
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
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
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
