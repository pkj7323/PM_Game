#include "stdafx.h"
#include "Earth.h"
#include "Shader.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"

Earth::Earth() : object("sphere")
{
	pos = { 120 + 100,0,-40 };
	scale = { 2,2,2 };
	rotation.x = 23.4f;
}

Earth::~Earth()
{
}

void Earth::Init()
{
	object::Init();
}

void Earth::Update()
{
	pos = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f * DT), glm::vec3(0, 1, 0)) * glm::vec4(pos, 1.0f);
	parentMatrix = glm::translate(glm::mat4(1.0f), { -200,0,-40 });
	rotation.y += 1.0f * DT * Planet_Rotation;
	object::Update();
}

void Earth::Draw(Shader& shader)
{
	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("earth"));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("earth_normal_map"));
	object::Draw(shader);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Earth::OnCollision(const string& group, object* other)
{
}

void Earth::OnCollisionEnd(const string& group, object* other)
{
}
