#pragma once
#include "stdafx.h"
class Shader
{
	SINGLE(Shader)
public:
	void make_ShaderProgram(const string& vertexPath, const string& fragmentPath);
	void Use()
	{
		glUseProgram(shaderProgramID);
	}
	GLuint GetID() {
		return this->shaderProgramID;
	}
	// -------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), static_cast<int>(value));
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()),static_cast<int>(value));
	}
	
private:
	GLint	make_fragmentShaders(const string& fragmentfile);
	GLint	make_vertexShaders(const string& vertexfile);
	string	filetobuf(const string& filename);
private:
	GLuint	shaderProgramID; //--- 세이더 프로그램이름
	

};