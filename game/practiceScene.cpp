#include "stdafx.h"
#include "practiceScene.h"
#include "Model.h"
#include "KeyManager.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Core.h"
#include "Cube.h"
#include "Earth.h"
#include "Mars.h"
#include "Mercury.h"
#include "ModelManager.h"
#include "Plane.h"
#include "SpaceShip.h"
#include "Venus.h"
#include "SoundManager.h"
#include "Sun.h"
#include "FrameBuffer.h"
#include "Rock.h"
#include "SkyBox.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"

practiceScene::practiceScene()
{
	pointLightPositions.emplace_back(0.7f, 0.2f, 2.0f);
	pointLightPositions.emplace_back(2.3f, -3.3f, -4.0f);
	pointLightPositions.emplace_back(-4.0f, 2.0f, -12.0f);
	pointLightPositions.emplace_back(0.0f, 0.0f, -3.0f);
}

practiceScene::~practiceScene()
{
	Scene::~Scene();
}

void practiceScene::Enter()
{
	m_camera = new Camera;
	m_vecObj.emplace_back(new Mercury);
	m_vecObj.emplace_back(new Venus);
	m_vecObj.emplace_back(new Earth);
	m_vecObj.emplace_back(new Mars);
	AddObject<Rock>();
	m_skyBox = new SkyBox;
	m_frameBuffer = new FrameBuffer;

	m_space_ship = new SpaceShip;
	sun = new Sun;
	m_cube = ModelManager::Instance()->GetModel("cube");

	ShaderManager::Instance()->SetUniformModel("ModelShader", pointLightPositions, *m_camera);
	ShaderManager::Instance()->SetUniformModel("Geo_ModelShader", pointLightPositions, *m_camera);
	SoundManager::Instance()->Play("bgm");
}

void practiceScene::Exit()
{
	delete m_camera;
	delete m_skyBox;
	delete m_frameBuffer;
	delete m_space_ship;
	delete sun;

	for (auto& obj : m_vecObj)
	{
		delete obj;
	}
	m_vecObj.clear();
	


}

void practiceScene::Update()
{
	if (KEY_TAP(KEY::ESC))
	{
		Core::Instance()->Release();
	}

	m_camera->Move();
	for (auto& obj : m_vecObj)
	{
		obj->Update();
	}
	sun->Update();
	m_space_ship->Move(*m_camera);
	m_space_ship->Update();
	pointLightPositions[0] = m_space_ship->GetLightPos1();
	pointLightPositions[1] = m_space_ship->GetLightPos2();
	pointLightPositions[2] = sun->GetPos();

	for (auto& obj : m_vecDeleteObj)
	{
		obj->Update();
	}
}

void practiceScene::Render()
{
	m_frameBuffer->Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	auto shader = ShaderManager::Instance()->GetShader("ModelShader");
	auto projection = m_camera->GetPerspectiveMatrix();
	auto view = m_camera->GetViewMatrix();
	glm::mat4 model = glm::mat4(1.0f);

	shader = ShaderManager::Instance()->GetShader("skyboxShader");
	auto skyBoxView = glm::mat4(glm::mat3(m_camera->GetViewMatrix())); //존나 중요함 이거 없으면 스카이박스가 카메라를 따라다님
	shader.Use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", skyBoxView);
	m_skyBox->Draw(shader);
	
	shader = ShaderManager::Instance()->GetShader("PlanetShader");
	shader.Use();
	shader.setInt("texture1", 0);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	model = glm::mat4(1.0f);
	shader.setMat4("model", model);
	sun->Draw(shader);

	Shader lightCubeShader = ShaderManager::Instance()->GetShader("LightCubeShader");
	lightCubeShader.Use();//조명의 위치를 보여주기위한 큐브들을 위한 쉐이더(모든색이 하얀색으로 설정됨)
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	// render the cube
	for (int i = 0; i < 4; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//스케일이 먼저 적용
		lightCubeShader.setMat4("model", model);
		m_cube.Draw(lightCubeShader);
	}

	shader = ShaderManager::Instance()->GetShader("ModelShader");
	shader.Use();
	shader.setVec3("viewPos", m_camera->GetPosition());
	shader.setVec3("spotLight.position", m_space_ship->GetLightPos3());//우주선의 앞부분 위치
	shader.setVec3("spotLight.direction", m_camera->GetFront());
	shader.setBool("blinn", blinn);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setVec3("pointLights[0].position", pointLightPositions[0]);
	shader.setVec3("pointLights[0].ambient", glm::vec3(0.05));//포인트 라이트의 주변광
	shader.setVec3("pointLights[0].diffuse", glm::vec3(0.8));

	shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	shader.setVec3("pointLights[1].ambient", glm::vec3(0.05));//포인트 라이트의 주변광
	shader.setVec3("pointLights[1].diffuse", glm::vec3(0.8));

	shader.setVec3("pointLights[2].position", sun->GetPos());
	shader.setVec3("pointLights[2].ambient", sun_ambient);//태양
	shader.setVec3("pointLights[2].diffuse", sun_diffuse);
	shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[2].constant", 0.001f);
	shader.setFloat("pointLights[2].linear", 0.001f);
	shader.setFloat("pointLights[2].quadratic", 0.001f);


	shader.setVec3("pointLights[3].position", pointLightPositions[3]);
	shader.setVec3("pointLights[3].ambient", glm::vec3(0.05));//포인트 라이트의 주변광
	shader.setVec3("pointLights[3].diffuse", glm::vec3(0.8));
	for (auto& obj : m_vecObj)
	{
		obj->Draw(shader);
	}
	m_space_ship->Draw(shader,*m_camera);

	shader = ShaderManager::Instance()->GetShader("Geo_ModelShader");
	shader.Use();
	shader.setVec3("viewPos", m_camera->GetPosition());
	shader.setVec3("spotLight.position", m_space_ship->GetLightPos3());//우주선의 앞부분 위치
	shader.setVec3("spotLight.direction", m_camera->GetFront());
	shader.setBool("blinn", blinn);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setVec3("pointLights[0].position", pointLightPositions[0]);
	shader.setVec3("pointLights[0].ambient", glm::vec3(0.05));//포인트 라이트의 주변광
	shader.setVec3("pointLights[0].diffuse", glm::vec3(0.8));

	shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	shader.setVec3("pointLights[1].ambient", glm::vec3(0.05));//포인트 라이트의 주변광
	shader.setVec3("pointLights[1].diffuse", glm::vec3(0.8));

	shader.setVec3("pointLights[2].position", sun->GetPos());
	shader.setVec3("pointLights[2].ambient", sun_ambient);//태양
	shader.setVec3("pointLights[2].diffuse", sun_diffuse);
	shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[2].constant", 0.001f);
	shader.setFloat("pointLights[2].linear", 0.001f);
	shader.setFloat("pointLights[2].quadratic", 0.001f);


	shader.setVec3("pointLights[3].position", pointLightPositions[3]);
	shader.setVec3("pointLights[3].ambient", glm::vec3(0.05));//포인트 라이트의 주변광
	shader.setVec3("pointLights[3].diffuse", glm::vec3(0.8));
	for (auto& obj: m_vecDeleteObj)
	{
		obj->Draw(shader);
	}

	m_frameBuffer->Render();
	glutSwapBuffers();
}

void practiceScene::mouse_motion(int x, int y)
{
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		last_x_ = xpos;
		last_y_ = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - last_x_;
	float yoffset = last_y_ - ypos; // reversed since y-coordinates go from bottom to top

	last_x_ = xpos;
	last_y_ = ypos;

	m_camera->ProcessMouseMovement(xoffset, yoffset);
	m_space_ship->ProcessMouseMovement(*m_camera);
	
	
	// 마우스를 중앙으로 이동

	glutWarpPointer(center_x_, center_y_);

	// 중앙으로 이동한 후의 위치를 lastX, lastY로 설정
	last_x_ = static_cast<float>(center_x_);
	last_y_ = static_cast<float>(center_y_);

}

void practiceScene::Mouse(int button, int state, int x, int y)
{
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		SoundManager::Instance()->Play("laser_effect");
		CollisionManager::Instance()->Mouse(button, state, x, y, *m_camera, m_space_ship->GetRayDes());
		m_space_ship->MouseClick();
	}


	if (firstMouse)
	{
		last_x_ = xpos;
		last_y_ = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - last_x_;
	float yoffset = last_y_ - ypos; // reversed since y-coordinates go from bottom to top

	last_x_ = xpos;
	last_y_ = ypos;
	
	m_camera->ProcessMouseMovement(xoffset, yoffset);
}

void practiceScene::mouse_wheel(int button, int dir, int x, int y)
{
	if (dir > 0)
	{
		m_camera->ProcessMouseScroll(1.0f);//fovy값변경
	}
	else
	{
		m_camera->ProcessMouseScroll(-1.0f);//fovy값변경
	}

}

void practiceScene::renderQuad()
{
	if (quadVAO == 0)
	{
		// positions
		glm::vec3 pos1(-1.0f, 1.0f, 0.0f);
		glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
		glm::vec3 pos3(1.0f, -1.0f, 0.0f);
		glm::vec3 pos4(1.0f, 1.0f, 0.0f);
		// texture coordinates
		glm::vec2 uv1(0.0f, 1.0f);
		glm::vec2 uv2(0.0f, 0.0f);
		glm::vec2 uv3(1.0f, 0.0f);
		glm::vec2 uv4(1.0f, 1.0f);
		// normal vector
		glm::vec3 nm(0.0f, 0.0f, 1.0f);

		// calculate tangent/bitangent vectors of both triangles
		glm::vec3 tangent1, bitangent1;
		glm::vec3 tangent2, bitangent2;
		// triangle 1
		// ----------
		glm::vec3 edge1 = pos2 - pos1;
		glm::vec3 edge2 = pos3 - pos1;
		glm::vec2 deltaUV1 = uv2 - uv1;
		glm::vec2 deltaUV2 = uv3 - uv1;

		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

		// triangle 2
		// ----------
		edge1 = pos3 - pos1;
		edge2 = pos4 - pos1;
		deltaUV1 = uv3 - uv1;
		deltaUV2 = uv4 - uv1;

		f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


		bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);


		float quadVertices[] = {
			// positions            // normal         // texcoords  // tangent                          // bitangent
			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
			pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
			pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
		};
		// configure plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}