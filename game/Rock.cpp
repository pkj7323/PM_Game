#include "stdafx.h"
#include "Rock.h"
#include "CollisionManager.h"

#include "TextureLoadManager.h"
#include "SpaceShip.h"
#include "TimeManager.h"

#include "random"

Rock::Rock() : object("rock")
{

	CollisionManager::Instance()->AddObject("Mouse:Rock", nullptr, this);

	pos = { randPos(math::dre),randPos(math::dre), -500};
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
	speed += 8.f * DT;
	pos += speed * DT * direction;
	rotation.x += speed * DT;
	object::Update();
}

void Rock::Draw(Shader& shader)
{	
	TextureLoadManager::Instance()->Use("rock");
	TextureLoadManager::Instance()->Use("rock_normal_map", 2);
	object::Draw(shader);
	TextureLoadManager::Instance()->Unbind(2);
}

void Rock::OnCollision(const string& group, object* other)
{
	if (group == "Mouse:Rock")
	{
		cout << "Rock Collision" << endl;
	}
}

void Rock::OnCollisionEnd(const string& group, object* other)
{
}

void Rock::SetDirection(const SpaceShip& spaceship)
{
	direction = glm::normalize(spaceship.GetPosition() - pos);
}




