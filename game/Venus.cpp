#include "stdafx.h"
#include "Venus.h"

#include "TextureLoadManager.h"

Venus::Venus() : object("sphere")
{
	pos = { 20,0,-60 };
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
