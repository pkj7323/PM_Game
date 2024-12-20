#pragma once
#include "Model.h"
class ModelManager
{
	SINGLE(ModelManager);
	unordered_map<string, Model> m_mapModel; 
public:
	void Init();
	void Update();
	void Render();
	void Release();
	void ModelLoad();
	void Load(const string& name, const string& filename);
	Model GetModel(const string& name);
};

