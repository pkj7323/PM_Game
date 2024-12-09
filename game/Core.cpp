#include "stdafx.h"
#include "Core.h"

#include "CollisionManager.h"
#include "KeyManager.h"
#include "ModelManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"

Core::Core()
= default;
Core::~Core()
= default;


void Core::Init()
{
	ModelManager::Instance()->Init();
	ShaderManager::Instance()->Init();
	TextureLoadManager::Instance()->Init();
	CollisionManager::Instance()->Init();
	KeyManager::Instance()->Init();


	SceneManager::Instance()->Init();
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
	CollisionManager::Instance()->Update();
	SceneManager::Instance()->Update();
}

void Core::Render()
{
	TimeManager::Instance()->Render();
	SceneManager::Instance()->Render();
	
}

void Core::Release()
{
	SceneManager::Instance()->Release();
	TextureLoadManager::Instance()->Release();
	ShaderManager::Instance()->Release();
	ModelManager::Instance()->Release();
}

void Core::mouse_motion(int x, int y)
{
	SceneManager::Instance()->mouse_motion(x, y);
}

void Core::Mouse(int button, int state, int x, int y)
{
	
	SceneManager::Instance()->Mouse(button, state, x, y);
}

void Core::mouse_wheel(int button, int dir, int x, int y)
{
	SceneManager::Instance()->mouse_wheel(button, dir, x, y);
}
