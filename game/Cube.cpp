#include "stdafx.h"
#include "Cube.h"

#include "TextureLoadManager.h"

Cube::Cube() : object("cube")
{
	std::uniform_real_distribution<float> randPos{ -25.f, 25.f };
	pos = { randPos(math::dre),0,randPos(math::dre) };
	scale = { 1,1,1 };
	rotation = { 0,0,0 };
}

Cube::~Cube()
{
}

void Cube::Init()
{
	object::Init();
}

void Cube::Update()
{
	object::Update();
}

void Cube::Draw(Shader& shader)
{
	
	TextureLoadManager::Instance()->Use("window", 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	object::Draw(shader);
	glDisable(GL_BLEND);
	TextureLoadManager::Instance()->Unbind(2);
}

void Cube::OnCollision(const string& group, object* other)
{
}

void Cube::OnCollisionEnd(const string& group, object* other)
{
}
