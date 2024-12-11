#include "stdafx.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "Camera.h"
ShaderManager::ShaderManager()
= default;
ShaderManager::~ShaderManager()
= default;

void ShaderManager::Init()
{
	{
		cout << "쉐이더 컴파일" << endl;
		MakeShader("asteroidShader", "asteroids_vs.glsl", "asteroids_fs.glsl");
		MakeShader("shader", "cubemap_vs.glsl", "cubemap_fs.glsl");
		MakeShader("screenShader", "framebuffer_screen_vs.glsl", "framebuffer_screen_fs.glsl");
		MakeShader("skyboxShader", "skybox_vs.glsl", "skybox_fs.glsl");
		MakeShader("ModelShader", "model_vertex.glsl", "model_fragment.glsl");
		MakeShader("Geo_ModelShader", "Vertex.glsl", "Fragment.glsl", "Geometry.glsl");
		

		MakeShader("LightCubeShader", "OldVertex.glsl", "OldFragment.glsl");
		MakeShader("cubeMapShader", "cubemap_vs.glsl", "cubemap_fs.glsl");
		MakeShader("stencilShader", "stencil_testing_vs.glsl", "stencil_testing_fs.glsl");
		MakeShader("stencilSingleColorShader", "stencil_testing_vs.glsl", "stencil_single_color_fs.glsl");
		MakeShader("PlanetShader", "Planet_vs.glsl", "Planet_fs.glsl");
		
		MakeShader("NormalMapShader","basic_light_vs.glsl","basic_light_fs.glsl");
		cout << "쉐이더 컴파일 종료" << endl;
	}
}

void ShaderManager::Update()
{
}

void ShaderManager::Release()
{
	
}

void ShaderManager::MakeShader(const string& name, const string& VSPath, const string& FSPath)
{
	if(m_mapShader.find(name) != m_mapShader.end())
	{
		cout << name << ": ";
		cout << "Shader name already exists" << endl;
		return;
	}
	Shader shader;
	cout << name << ": ";
	shader.make_ShaderProgram(VSPath, FSPath);
	m_mapShader[name] = shader;
}

void ShaderManager::MakeShader(const string& name, const string& VSPath, const string& FSPath, const string& GSPath)
{
	if (m_mapShader.find(name) != m_mapShader.end())
	{
		cout << name << " : " << "Shader name already exists" << endl;
		return;
	}
	Shader shader;
	cout << name << ": ";
	shader.make_ShaderProgram(VSPath, FSPath, GSPath);
	m_mapShader[name] = shader;
}

void ShaderManager::SetUniformModel(const string& name, const vector<glm::vec3>& light_pos, const Camera& camera)
{
	Shader ModelShader = GetShader(name);
	auto projection = camera.GetPerspectiveMatrix();
	auto view = camera.GetViewMatrix();
	glm::vec3 pointLightColor{ 0.8f,0.8f,0.8f };
	ModelShader.Use();

	ModelShader.setMat4("projection", projection);
	ModelShader.setMat4("view", view);
	ModelShader.setMat4("model", glm::mat4(1.0f));
	ModelShader.setVec3("viewPos", camera.GetPosition());

	ModelShader.setBool("blinn", true);
	ModelShader.setFloat("material.shininess", 32.0f);

	ModelShader.setVec3("dirLight.direction", 0.5f, -1.0f, 5.0f);
	ModelShader.setVec3("dirLight.ambient", 0.02f, 0.02f, 0.02f);
	ModelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	ModelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	//포인트 라이트의 위치
	ModelShader.setVec3("pointLights[0].position", light_pos[0]);
	ModelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);//포인트 라이트의 주변광
	ModelShader.setVec3("pointLights[0].diffuse", pointLightColor);//포인트 라이트의 확산광
	ModelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);//포인트 라이트의 반사광
	ModelShader.setFloat("pointLights[0].constant", 1.0f);//포인트 라이트의 상수값
	ModelShader.setFloat("pointLights[0].linear", 0.09f);//포인트 라이트의 선형값(1차)
	ModelShader.setFloat("pointLights[0].quadratic", 0.032f);//포인트 라이트의 이차값(2차)

	ModelShader.setVec3("pointLights[1].position", light_pos[1]);
	ModelShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[1].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[1].constant", 1.0f);
	ModelShader.setFloat("pointLights[1].linear", 0.09f);
	ModelShader.setFloat("pointLights[1].quadratic", 0.032f);


	ModelShader.setVec3("pointLights[2].position", light_pos[2]);
	ModelShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[2].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[2].constant", 1.0f);
	ModelShader.setFloat("pointLights[2].linear", 0.09f);
	ModelShader.setFloat("pointLights[2].quadratic", 0.032f);


	ModelShader.setVec3("pointLights[3].position", light_pos[3]);
	ModelShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[3].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[3].constant", 1.0f);
	ModelShader.setFloat("pointLights[3].linear", 0.09f);
	ModelShader.setFloat("pointLights[3].quadratic", 0.032f);


	ModelShader.setVec3("spotLight.position", camera.GetPosition());
	ModelShader.setVec3("spotLight.direction", camera.GetFront());
	ModelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	ModelShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	ModelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("spotLight.constant", 1.0f);
	ModelShader.setFloat("spotLight.linear", 0.09f);
	ModelShader.setFloat("spotLight.quadratic", 0.032f);
	ModelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	//손전등의 안쪽조명을 받을 각도
	ModelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));


	ModelShader.setInt("material.diffuse", 0);
	ModelShader.setInt("material.specular", 1);
	ModelShader.setInt("material.normalMap", 2);
}

Shader ShaderManager::GetShader(const string& name)
{
	if (m_mapShader.find(name) == m_mapShader.end())
	{
		cout << name << ": ";
		cout << "Shader name not found" << endl;
		return Shader();
	}
	else
	{
		//cout << "Shader name found" << endl;
		return m_mapShader[name];
	}
}
