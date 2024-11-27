#pragma once
#include "Shader.h"
class ShaderManager
{
	SINGLE(ShaderManager)

	unordered_map<string, Shader> m_mapShader;
public:
	void Init();
	void Update();
	void MakeShader(const string& name, const string& VSPath, const string& FSPath);
	void MakeShader(const string& name, const string& VSPath, const string& FSPath,const string& GSPath);
	Shader GetShader(const string& name);
};
