#include "stdafx.h"
#include "ShaderManager.h"
#include "Shader.h"
ShaderManager::ShaderManager()
{
}
ShaderManager::~ShaderManager()
{
	for (auto& shader : m_mapShader)
	{
		delete shader.second;
	}
	m_mapShader.clear();
}


void ShaderManager::Init()
{
	m_mapShader = {};
}

void ShaderManager::Update()
{
}

void ShaderManager::MakeShader(const string& name, const string& VSPath, const string& FSPath)
{
	if(m_mapShader.find(name) != m_mapShader.end())
	{
		cout << "Shader name already exists" << endl;
		return;
	}
	Shader* shader = new Shader;
	shader->make_ShaderProgram(VSPath, FSPath);
	m_mapShader[name] = shader;
}

Shader* ShaderManager::GetShader(const string& name)
{
	if (m_mapShader.find(name) == m_mapShader.end())
	{
		cout << "Shader name not found" << endl;
		return nullptr;
	}
	return m_mapShader[name];
}
