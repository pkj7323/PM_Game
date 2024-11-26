#include "stdafx.h"
#include "SceneManager.h"
#include "IntroScene.h"
SceneManager::SceneManager()
{
	m_CurrScene = nullptr;
	arrScene.resize(static_cast<int>(SCENE_TYPE::END));
}
SceneManager::~SceneManager()
{
}


void SceneManager::Init()
{
	arrScene[static_cast<UINT>(SCENE_TYPE::INTRO)] = new IntroScene;
	arrScene[static_cast<UINT>(SCENE_TYPE::INTRO)]->SetName("StartScene");

	m_CurrScene = arrScene[static_cast<UINT>(SCENE_TYPE::START)];
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
