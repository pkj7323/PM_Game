#include "stdafx.h"
#include "SceneManager.h"
#include "IntroScene.h"
#include "practiceScene.h"



void SceneManager::Init()
{
	m_CurrScene = nullptr;
	arrScene.resize(static_cast<int>(SCENE_TYPE::END));

	arrScene[static_cast<UINT>(SCENE_TYPE::INTRO)] = new practiceScene;
	arrScene[static_cast<UINT>(SCENE_TYPE::INTRO)]->SetName("StartScene");

	m_CurrScene = arrScene[static_cast<UINT>(SCENE_TYPE::INTRO)];
	m_CurrScene->Enter();
}

void SceneManager::Update()
{
	m_CurrScene->Update();
}

void SceneManager::Render()
{
	m_CurrScene->Render();
}

void SceneManager::Release()
{
	delete m_CurrScene;
	m_CurrScene = nullptr;
	arrScene.clear();
}

void SceneManager::mouse_motion(int x, int y)
{
	m_CurrScene->mouse_motion(x, y);
}

void SceneManager::Mouse(int button, int state, int x, int y)
{
	m_CurrScene->Mouse(button, state, x, y);
}

void SceneManager::mouse_wheel(int button, int dir, int x, int y)
{
	m_CurrScene->mouse_wheel(button, dir, x, y);
}
