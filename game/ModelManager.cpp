#include "stdafx.h"
#include "ModelManager.h"
#include "Model.h"


void ModelManager::Init()
{
	cout << "ModelManager Init" << endl;
	Load("rock", "resources/rock/rock.obj");
	Load("plane", "resources/plane.obj");
	//Load("pyramid", "resources/pyramid.obj");
	Load("cube", "resources/cube.obj");
	//Load("sphere", "resources/sphere.obj");
	Load("planet", "resources/planet.obj");
	Load("backpack", "resources/backpack.obj");
	Load("space_ship", "resources/space_ship.obj");
	Load("earth", "resources/earth/earth.obj");
	cout << "ModelManager Init end" << endl;
}

void ModelManager::Update()
{
}

void ModelManager::Render()
{
}

void ModelManager::Release()
{
	
}

void ModelManager::Load(const string& name, const string& filename)
{
	if (m_mapModel.find("name") != m_mapModel.end())
	{
		cout << "Model name already exists" << endl;
		return;
	}
	m_mapModel[name] = Model(filename);
	return;
}

Model ModelManager::GetModel(const string& name)
{
	if (m_mapModel.find(name) == m_mapModel.end())
	{
		cout << name << ": ";
		cout << "Model name not found" << endl;
		return Model();
	}
	return m_mapModel[name];
}


