#include "stdafx.h"
#include "Venus.h"

#include "TextureLoadManager.h"
#include "TimeManager.h"

Venus::Venus() : object("sphere")
{
	pos = { 80 + 100,0,-40 };
	scale = { 1.5,1.5,1.5 };
}

Venus::~Venus()
{
}

void Venus::Init()
{
	object::Init();
}

void Venus::Update()
{
	pos = glm::rotate(glm::mat4(1.0f), glm::radians(1.61f * DT), glm::vec3(0, 1, 0)) * glm::vec4(pos, 1.0f);
	parentMatrix = glm::translate(glm::mat4(1.0f), { -200,0,-40 });
	object::Update();
}

void Venus::Draw(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("venus_surface"));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("venus_surface_normal_map"));
	object::Draw(shader);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Venus::OnCollision(const string& group, object* other)
{
}

void Venus::OnCollisionEnd(const string& group, object* other)
{
}
