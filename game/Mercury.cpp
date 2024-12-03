#include "stdafx.h"
#include "Mercury.h"

#include "Shader.h"
#include "TextureLoadManager.h"

Mercury::Mercury() : object("sphere")
{
	pos = { 10,0,0 };
	scale = { 0.3,0.3,0.3 };
}

Mercury::~Mercury()
{
}

void Mercury::Init()
{
	object::Init();
}

void Mercury::Update()
{
	pos = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.f, 1.f, 0.f))
		* glm::vec4(pos, 1.0f);
	object::Update();
}

void Mercury::Draw(Shader& shader)
{
	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("mercury"));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("mercury_normal_map"));
	object::Draw(shader);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mercury::OnCollision(const string& group, object* other)
{
}

void Mercury::OnCollisionEnd(const string& group, object* other)
{
}
