#pragma once
#include "stdafx.h"
class Shader
{
public:
	Shader();
	~Shader();
	Shader(const string& vertexPath, const string& fragmentPath)
	{
		make_ShaderProgram(vertexPath, fragmentPath);
	}
	Shader(const string& vertexPath, const string& fragmentPath, const string& geometryPath)
	{
		make_ShaderProgram(vertexPath, fragmentPath);
		
	}
	void make_ShaderProgram(const string& vertexPath, const string& fragmentPath);
	void make_ShaderProgram(const string& vertexPath, const string& fragmentPath,const string& geometryPath);
	

	void Use()
	{
		glUseProgram(shaderProgramID);
	}
	GLuint GetID() {
		return this->shaderProgramID;
	}
	GLint findLocation(const string& name) const;


	// -------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const;
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w) const;
    // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	GLint	make_fragmentShaders(const string& fragmentfile);
	GLint	make_vertexShaders(const string& vertexfile);
	GLint	make_geometryShaders(const string& geometryfile);
	string	filetobuf(const string& filename);
private:
	GLuint	shaderProgramID; //--- 세이더 프로그램이름

};