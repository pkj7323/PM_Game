#include "stdafx.h"
#include "ShaderManager.h"
#include "Shader.h"
ShaderManager::ShaderManager()
{
}
ShaderManager::~ShaderManager()
{
	m_mapShader.clear();
}


void ShaderManager::Init()
{
	{
		cout << "쉐이더 컴파일" << endl;
		//ShaderManager::Instance()->MakeShader("shader", "cubemap_vs.glsl", "cubemap_fs.glsl");
		//ShaderManager::Instance()->MakeShader("screenShader", "framebuffer_screen_vs.glsl", "framebuffer_screen_fs.glsl");
		//ShaderManager::Instance()->MakeShader("skyboxShader", "skybox_vs.glsl", "skybox_fs.glsl");
		//ShaderManager::Instance()->MakeShader("ModelShader", "model_vertex.glsl", "model_fragment.glsl");
		//ShaderManager::Instance()->MakeShader("lightCubeShader", "OldVertex.glsl", "OldFragment.glsl");
		//ShaderManager::Instance()->MakeShader("cubeMapShader", "cubemap_vs.glsl", "cubemap_fs.glsl");
		//ShaderManager::Instance()->MakeShader("stencilShader", "stencil_testing_vs.glsl", "stencil_testing_fs.glsl");
		//ShaderManager::Instance()->MakeShader("stencilSingleColorShader", "stencil_testing_vs.glsl", "stencil_single_color_fs.glsl");
		cout << "쉐이더 컴파일 종료" << endl;
	}
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
	Shader shader;
	shader.make_ShaderProgram(VSPath, FSPath);
	m_mapShader[name] = shader;
}

void ShaderManager::MakeShader(const string& name, const string& VSPath, const string& FSPath, const string& GSPath)
{
	if (m_mapShader.find(name) != m_mapShader.end())
	{
		cout << "Shader name already exists" << endl;
		return;
	}
	Shader shader;
	shader.make_ShaderProgram(VSPath, FSPath, GSPath);
	m_mapShader[name] = shader;
}

Shader ShaderManager::GetShader(const string& name)
{
	if (m_mapShader.find(name) == m_mapShader.end())
	{
		cout << "Shader name not found" << endl;
		return Shader();
	}
	else
	{
		//cout << "Shader name found" << endl;
		return m_mapShader[name];
	}
}
