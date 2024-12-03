#include "stdafx.h"
#include "Snow.h"

#include "TextureLoadManager.h"
#include "TimeManager.h"

Snow::Snow() : object("sphere")
{
	
	speed = randSpeed(dre);
	pos = { randPos(dre), 40, randPos(dre) };
	scale = { 0.05,0.05,0.05 };
}

Snow::~Snow()
{
}

void Snow::Init()
{
	object::Init();
}

void Snow::Update()
{
	speed += 8.2f * DT;
	pos.y -= 0.1f * speed * DT;
	if (pos.y <= 0)
	{
		pos.y = 40;
		speed = randSpeed(dre);
	}
	object::Update();
}

void Snow::Draw(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("snow"));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("snow_normal_map"));
	object::Draw(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Snow::OnCollision(const string& group, object* other)
{
}

void Snow::OnCollisionEnd(const string& group, object* other)
{
}
