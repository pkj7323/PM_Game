#include "stdafx.h"
#include "Plane.h"

#include "TextureLoadManager.h"

Plane::Plane() : object("plane")
{
	pos.y = -1.f;
}

Plane::~Plane()
{
}

void Plane::Init()
{
	object::Init();
}

void Plane::Update()
{
	object::Update();
}

void Plane::Draw(Shader& shader)
{
    TextureLoadManager::Instance()->Use("brick_wall", 0);
    TextureLoadManager::Instance()->Use("brick_wall_normal", 2);
    object::Draw(shader);
    TextureLoadManager::Instance()->Unbind();
}

void Plane::OnCollision(const string& group, object* other)
{
}

void Plane::OnCollisionEnd(const string& group, object* other)
{
}
