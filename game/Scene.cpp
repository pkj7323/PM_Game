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
	for (auto& obj : m_vecDeleteObj)
	{
		delete obj;
	}
	m_vecDeleteObj.clear();
}



