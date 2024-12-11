#include "stdafx.h"
#include "TextureLoadManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureLoadManager::TextureLoadManager()
= default;
TextureLoadManager::~TextureLoadManager()
= default;

void TextureLoadManager::Init()
{
	
	Load("TUK", "resources/tuk_credit.png");
	
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		// 튜토리얼을 위해 반투명한 테두리를 방지하기 위해 GL_CLAMP_TO_EDGE를 사용합니다. 보간으로 인해 다음 반복에서 텍셀을 가져옵니다.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
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

void TextureLoadManager::TexturesLoad()
{
	cout << "텍스쳐 로드" << endl;
	Load("wall", "wall.jpg");
	Load("brick_wall", "resources/brick/brickwall.jpg");
	Load("brick_wall_normal", "resources/brick/brickwall_normal.jpg");

	Load("container2", "container2.png");
	Load("container2_specular", "container2_specular.png");
	Load("marble", "resources/marble.jpg");
	Load("metal", "resources/metal.png");

	Load("mars", "resources/2k_mars.jpg");
	Load("mars_normal_map", "resources/2k_mars_normal.png");

	Load("earth", "resources/earth/earth.jpg");
	Load("earth_normal_map", "resources/earth/earth_normal_map.jpg");

	Load("sun", "resources/sun.jpg");
	Load("sun_normal_map", "resources/sun_normal.png");

	Load("mercury", "resources/mercury.jpg");
	Load("mercury_normal_map", "resources/mercury_normal.png");

	Load("venus_surface", "resources/venus_surface.jpg");
	Load("venus_surface_normal_map", "resources/venus_surface_normal.png");

	Load("venus_atmosphere", "resources/venus_atmosphere.jpg");
	Load("venus_atmosphere_normal_map", "resources/venus_atmosphere_normal.png");

	Load("snow", "resources/snow.jpg");
	Load("snow_normal_map", "resources/snow_normal.png");

	Load("cyan", "resources/Cyan.png");
	Load("window", "resources/blending_transparent_window.png");
	Load("laser_effect", "resources/laser_effect.png");
	vector<std::string> faces
	{
		"resources/skybox/right.png",
		"resources/skybox/left.png",
		"resources/skybox/top.png",
		"resources/skybox/bottom.png",
		"resources/skybox/front.png",
		"resources/skybox/back.png"
	};
	loadCubeMap("skybox", faces);//스카이박스 텍스쳐 로드
	//스카이박스는 로드가 다르다. 큐브맵함수들을 사용해서 로드하고 여러장의 사진 필요하기 에 faces벡터배열을 넘겨준다.
	cout << "텍스쳐 로드 종료" << endl;
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

void TextureLoadManager::Unbind(GLuint index)
{
	for (int i = 0; i < index; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
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
