#include "stdafx.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager() : shaderProgramID(NULL)
{
}
ShaderManager::~ShaderManager()
{
}

void ShaderManager::make_ShaderProgram(const string& vertexPath, const string& fragmentPath)
{
	GLint vertexShader = make_vertexShaders(vertexPath);
	GLint fragmentShader = make_fragmentShaders(fragmentPath);
	shaderProgramID = glCreateProgram();				//--- 세이더프로그램만들기

	glAttachShader(shaderProgramID, vertexShader);		//--- 세이더프로그램에버텍스세이더붙이기
	glAttachShader(shaderProgramID, fragmentShader);	//--- 세이더프로그램에프래그먼트세이더붙이기

	glLinkProgram(shaderProgramID);				//--- 세이더프로그램링크하기

	glDeleteShader(vertexShader);				//--- 세이더객체를세이더프로그램에링크했음으로,세이더객체자체는삭제가능
	glDeleteShader(fragmentShader);				// ---세이더가 잘연결되었는지체크하기

	GLint result = 0;
	GLchar errorLog[512];

	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return;
	}
	else
	{
		std::cout << "shader program 연결 성공\n";
		glUseProgram(shaderProgramID);
		//initBuffer();
	}
}


GLint ShaderManager::make_fragmentShaders(const string& fragmentfile)
{
	string buf = filetobuf(fragmentfile);
	const GLchar* fragmentSource = buf.c_str();


	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result = GL_FALSE;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "Error: Fragment shader compilation failed\n" << errorLog << std::endl;
		return GL_FALSE;
	}
	else
	{
		return fragmentShader;
	}
}

GLint ShaderManager::make_vertexShaders(const string& vertexfile)
{
	string buf = filetobuf(vertexfile);

	const GLchar* vertexSource = buf.c_str();
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLint result = GL_FALSE;
	GLchar errorLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "Error: Vertex shader compilation failed\n" << errorLog << std::endl;
		return GL_FALSE;
	}
	else
	{
		return vertexShader;
	}
}

string ShaderManager::filetobuf(const string& filename)
{
	string buf{};
	ifstream vertexShaderFile(filename);
	if (vertexShaderFile.is_open())
	{
		string line;
		while (getline(vertexShaderFile, line))
		{
			buf += line + "\n";
		}
		vertexShaderFile.close();
	}
	else
	{
		cout << "Unable to open vertex shader file" << std::endl;
		exit(EXIT_FAILURE);
	}
	return buf;
}

GLint ShaderManager::findLocation(const string& name) const
{
	return glGetUniformLocation(shaderProgramID, name.c_str());
}

// -------------------------------------------------------------------------
void ShaderManager::setBool(const std::string& name, bool value) const
{
	
	glUniform1i(findLocation(name), (int)value);
}
// ------------------------------------------------------------------------
void ShaderManager::setInt(const std::string& name, int value) const
{
	glUniform1i(findLocation(name), value);
}
// ------------------------------------------------------------------------
void ShaderManager::setFloat(const std::string& name, float value) const
{
	glUniform1f(findLocation(name), value);
}
// ------------------------------------------------------------------------
void ShaderManager::setVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(findLocation(name), 1, glm::value_ptr(value));
}
void ShaderManager::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(findLocation(name), x, y);
}
// ------------------------------------------------------------------------
void ShaderManager::setVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(findLocation(name), 1, glm::value_ptr(value));
}
void ShaderManager::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(findLocation(name), x, y, z);
}
// ------------------------------------------------------------------------
void ShaderManager::setVec4(const std::string& name, const glm::vec4& value) const
{
	glUniform4fv(findLocation(name), 1, glm::value_ptr(value));
}
void ShaderManager::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(findLocation(name), x, y, z, w);
}
// ------------------------------------------------------------------------
void ShaderManager::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(findLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}
// ------------------------------------------------------------------------
void ShaderManager::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(findLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}
// ------------------------------------------------------------------------
void ShaderManager::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(findLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}

