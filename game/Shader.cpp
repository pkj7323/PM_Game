#include "stdafx.h"
#include "Shader.h"

Shader::Shader() : shaderProgramID(NULL)
{
}
Shader::~Shader()
{
}

void Shader::make_ShaderProgram(const string& vertexPath, const string& fragmentPath)
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


GLint Shader::make_fragmentShaders(const string& fragmentfile)
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

GLint Shader::make_vertexShaders(const string& vertexfile)
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

string Shader::filetobuf(const string& filename)
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


