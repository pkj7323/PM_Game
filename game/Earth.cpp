#include "stdafx.h"
#include "Earth.h"

#include "Shader.h"
#include "TextureLoadManager.h"

Earth::Earth() : object("sphere")
{
	pos = { 30,0,0 };
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
	pos = glm::rotate(glm::mat4(1.0f), glm::radians(0.5f), glm::vec3(0.f, 1.f, 0.f))
		* glm::vec4(pos, 1.0f);
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
