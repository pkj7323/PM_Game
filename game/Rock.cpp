#include "stdafx.h"
#include "Rock.h"
#include "CollisionManager.h"


Rock::Rock() : object("rock")
{
	CollisionManager::Instance()->AddObject("Mouse:Rock", nullptr, this);
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
	rotation.z += 0.5f;

	object::Update();
}

void Rock::Draw(Shader& shader)
{
	object::Draw(shader);
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




