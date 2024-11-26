#include "stdafx.h"
#include "Scene.h"

#include "object.h"

Scene::~Scene()
{
	for (auto& obj : m_vecObj)
	{
		delete obj;
	}
	m_vecObj.clear();
}

void Scene::Update()
{
	for (auto& obj:m_vecObj)
	{
		obj->Update();
	}

}

void Scene::Render()
{
	for (auto& obj : m_vecObj)
	{
		obj->Draw();
	}
}