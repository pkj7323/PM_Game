#include "stdafx.h"
#include "Mercury.h"

#include "Shader.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"

Mercury::Mercury() : object("sphere")
{
	pos = { 30 + 100,0,-40 };
	scale = { 1,1,1 };
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
	pos = glm::rotate(glm::mat4(1.0f), glm::radians(4.17f * DT), glm::vec3(0, 1, 0)) * glm::vec4(pos, 1.0f);
	parentMatrix = glm::translate(glm::mat4(1.0f), { -200,0,-40 });
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
