#include "stdafx.h"
#include "Core.h"

#include "CollisionManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"

Core::Core()
{
}

Core::~Core()
{
}


void Core::Init()
{
	SceneManager::Instance()->Init();
	TextureLoadManager::Instance()->Init();
	CollisionManager::Instance()->Init();
	KeyManager::Instance()->Init();
}

void Core::Progress()
{
	Update();
	Render();
}

void Core::Update()
{
	TimeManager::Instance()->Update();
	KeyManager::Instance()->Update();
	SceneManager::Instance()->Update();
	CollisionManager::Instance()->Update();
}

void Core::Render()
{
	SceneManager::Instance()->Render();

}

void Core::Release()
{
}
