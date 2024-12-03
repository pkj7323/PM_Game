#pragma once
#include "Shader.h"
class Camera;
class ShaderManager
{
	SINGLE(ShaderManager)

	unordered_map<string, Shader> m_mapShader;
public:
	void Init();
	void Update();
	void Release();
	void MakeShader(const string& name, const string& VSPath, const string& FSPath);
	void MakeShader(const string& name, const string& VSPath, const string& FSPath,const string& GSPath);
	void SetUniformModel(const string& name, const vector<glm::vec3>& light_pos, const Camera& camera );
	Shader GetShader(const string& name);
};
