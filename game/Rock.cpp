#include "stdafx.h"
#include "Rock.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "SpaceShip.h"

Rock::Rock() : object("rock")
{
	CollisionManager::Instance()->AddObject("Mouse:Rock", nullptr, this);
	pos = { randPos(math::dre),randPos(math::dre), -100 };
	speed = randSpeed(math::dre);
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
	if (isDead)
	{
		
	}
	else
	{
		speed += 8.f * DT;
		pos += speed * DT * direction;
		rotation.x += speed * DT;
	}

	if (pos.x > 500 || pos.x < -500 || pos.y > 500 || pos.y < -500 || pos.z > 500 || pos.z < -600)
	{
		isDead = true;
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
	if (group == "Mouse:Rock" && isDead == false)
	{
		SoundManager::Instance()->Play("explosion_effect");
		SceneManager::Instance()->CurrentSceneDeleteObject<Rock>(this);
		isDead = true;
	}
}

void Rock::OnCollisionEnd(const string& group, object* other)
{
}

void Rock::SetDirection(const SpaceShip& spaceship)
{
	direction = glm::normalize(spaceship.GetPos() - pos);
}




