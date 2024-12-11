#include "stdafx.h"
#include "Scene.h"

#include "object.h"

Scene::~Scene()
{
	
	m_vecObj.clear();
	m_vecDeleteObj.clear();
}



