﻿#include "stdafx.h"
#include "Sun.h"

#include "TextureLoadManager.h"

Sun::Sun() : object("sphere")
{
	pos = { -200,0,-40 };
	scale = { 20,20,20 };
}

Sun::~Sun()
{
}

void Sun::Init()
{
	object::Init();
}

void Sun::Init(const string& name)
{
	object::Init(name);
}

void Sun::Update()
{
	object::Update();
}

void Sun::Draw(Shader& shader)
{
	TextureLoadManager::Instance()->Use("sun");
	TextureLoadManager::Instance()->Use("sun_normal_map",2);
	object::Draw(shader);
	TextureLoadManager::Instance()->Unbind(2);
}

void Sun::OnCollision(const string& group, object* other)
{
}

void Sun::OnCollisionEnd(const string& group, object* other)
{
}
