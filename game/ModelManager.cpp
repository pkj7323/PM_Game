#include "stdafx.h"
#include "ModelManager.h"
#include "Model.h"


void ModelManager::Init()
{
	Load("rock", "resources/rock/rock.obj");
	Load("plane", "resources/plane.obj");
	Load("pyramid", "resources/pyramid.obj");
	Load("cube", "resources/cube.obj");
	Load("sphere", "resources/sphere.obj");
}

void ModelManager::Update()
{
}

void ModelManager::Render()
{
}

void ModelManager::Release()
{
	for (auto& iter : m_mapModel)
	{
		delete iter.second;
	}
	m_mapModel.clear();
}

void ModelManager::Load(const string& name, const string& filename)
{
	if (m_mapModel.find("name") != m_mapModel.end())
	{
		cout << "Model name already exists" << endl;
	}
	Model* model = new Model(filename);
	m_mapModel[name] = model;
}

Model* ModelManager::GetModel(const string& name)
{
	if (m_mapModel.find(name) == m_mapModel.end())
	{
		cout << "Model name not found" << endl;
		return nullptr;
	}
	return m_mapModel[name];
}


