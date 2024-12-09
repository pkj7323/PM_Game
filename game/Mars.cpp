#include "stdafx.h"
#include "Mars.h"

#include "TextureLoadManager.h"

Mars::Mars() : object("sphere")
{
	pos = { 0,0,0 };
	scale = { 2,2,2 };
}

Mars::~Mars()
{
}

void Mars::Init()
{
	object::Init();
}

void Mars::Init(const string& name)
{
	object::Init(name);
}

void Mars::Update()
{
	object::Update();
}

void Mars::Draw(Shader& shader)
{
	TextureLoadManager::Instance()->Use("mars");
	TextureLoadManager::Instance()->Use("mars_normal_map",2);
	object::Draw(shader);
	TextureLoadManager::Instance()->Unbind(2);
}

void Mars::OnCollision(const string& group, object* other)
{
}

void Mars::OnCollisionEnd(const string& group, object* other)
{
}
