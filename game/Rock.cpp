#include "stdafx.h"
#include "Rock.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "SoundManager.h"
#include "TimeManager.h"


Rock::Rock() : object("rock")
{
	CollisionManager::Instance()->AddObject("Mouse:Rock", nullptr, this);
	pos = { 0, 0, 0 };
	bs.center={ 0, 0.5, 0 };
	bs.radius = 2;
}

Rock::~Rock()
{
}

void Rock::Init()
{
	object::Init();
}

void Rock::Update()
{
	rotation.y += 0.5f;
	//rotation.z += 0.5f;
	if (isDead)
	{
		timer += DT;
		if (timer >= time_to_die)
		{
			SceneManager::Instance()->CurrentSceneDeleteDeleteObject<Rock>(this);
		}
	}
	object::Update();
}

void Rock::Draw(Shader& shader)
{
	shader.setFloat("time", timer);
	object::Draw(shader);
}

void Rock::OnCollision(const string& group, object* other)
{
	if (group == "Mouse:Rock")
	{
		SoundManager::Instance()->Play("explosion_effect");
		SceneManager::Instance()->CurrentSceneDeleteObject<Rock>(this);
		isDead = true;
	}
}

void Rock::OnCollisionEnd(const string& group, object* other)
{
}




