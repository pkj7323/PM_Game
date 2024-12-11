#include "stdafx.h"
#include "Earth.h"

#include "Shader.h"
#include "TextureLoadManager.h"

Earth::Earth() : object("sphere")
{
	pos = { 30,0,-50 };
	scale = { 2,2,2 };
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
