﻿#include "stdafx.h"
#include "practiceScene.h"
#include "Model.h"
#include "KeyManager.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "Earth.h"
#include "Mercury.h"
#include "ModelManager.h"
#include "Plane.h"
#include "Pyramid.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"
#include "rock.h"
#include "Snow.h"
#include "Venus.h"


practiceScene::practiceScene()
{
	pointLightPositions.emplace_back(0.7f, 0.2f, 2.0f);
	pointLightPositions.emplace_back(2.3f, -3.3f, -4.0f);
	pointLightPositions.emplace_back(-4.0f, 2.0f, -12.0f);
	pointLightPositions.emplace_back(0.0f, 0.0f, -3.0f);
	pointLightColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

practiceScene::~practiceScene()
{
}

void practiceScene::Enter()
{
	m_camera = new Camera;
	m_objects.emplace_back(new Mercury);
	m_objects.emplace_back(new Venus);
	m_objects.emplace_back(new Earth);
	m_objects.emplace_back(new Plane);
	m_pyramid = new Pyramid;
	for (int i = 0; i < 100; i++)
	{
		m_objects.emplace_back(new Snow);
	}

	m_cube = ModelManager::Instance()->GetModel("cube");
	//Shader ModelShader = ShaderManager::Instance()->GetShader("ModelShader");
	//auto projection = m_camera->GetPerspectiveMatrix();
	//auto view = m_camera->GetViewMatrix();
	//ModelShader.Use();
	//
	//ModelShader.setMat4("projection", projection);
	//ModelShader.setMat4("view", view);
	//ModelShader.setMat4("model", glm::mat4(1.0f));
	//ModelShader.setVec3("viewPos", m_camera->GetPosition());
	//
	//ModelShader.setBool("blinn", true);
	//ModelShader.setFloat("material.shininess", 32.0f);
	//
	//ModelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	//ModelShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	//ModelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	//ModelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
	//
	////포인트 라이트의 위치
	//ModelShader.setVec3("pointLights[0].position", pointLightPositions[0]);
	//ModelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);//포인트 라이트의 주변광
	//ModelShader.setVec3("pointLights[0].diffuse", pointLightColor);//포인트 라이트의 확산광
	//ModelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);//포인트 라이트의 반사광
	//ModelShader.setFloat("pointLights[0].constant", 1.0f);//포인트 라이트의 상수값
	//ModelShader.setFloat("pointLights[0].linear", 0.09);//포인트 라이트의 선형값(1차)
	//ModelShader.setFloat("pointLights[0].quadratic", 0.032);//포인트 라이트의 이차값(2차)
	//
	//ModelShader.setVec3("pointLights[1].position", pointLightPositions[1]);
	//ModelShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	//ModelShader.setVec3("pointLights[1].diffuse", pointLightColor);
	//ModelShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	//ModelShader.setFloat("pointLights[1].constant", 1.0f);
	//ModelShader.setFloat("pointLights[1].linear", 0.09f);
	//ModelShader.setFloat("pointLights[1].quadratic", 0.032f);
	//
	//
	//ModelShader.setVec3("pointLights[2].position", pointLightPositions[2]);
	//ModelShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	//ModelShader.setVec3("pointLights[2].diffuse", pointLightColor);
	//ModelShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	//ModelShader.setFloat("pointLights[2].constant", 1.0f);
	//ModelShader.setFloat("pointLights[2].linear", 0.09f);
	//ModelShader.setFloat("pointLights[2].quadratic", 0.032f);
	//
	//
	//ModelShader.setVec3("pointLights[3].position", pointLightPositions[3]);
	//ModelShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	//ModelShader.setVec3("pointLights[3].diffuse", pointLightColor);
	//ModelShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	//ModelShader.setFloat("pointLights[3].constant", 1.0f);
	//ModelShader.setFloat("pointLights[3].linear", 0.09f);
	//ModelShader.setFloat("pointLights[3].quadratic", 0.032f);
	//
	//
	//ModelShader.setVec3("spotLight.position", m_camera->GetPosition());
	//ModelShader.setVec3("spotLight.direction", m_camera->GetFront());
	//ModelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	//ModelShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	//ModelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	//ModelShader.setFloat("spotLight.constant", 1.0f);
	//ModelShader.setFloat("spotLight.linear", 0.09f);
	//ModelShader.setFloat("spotLight.quadratic", 0.032f);
	//ModelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	////손전등의 안쪽조명을 받을 각도
	//ModelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	//
	//
	//ModelShader.setInt("material.diffuse", 0);
	//ModelShader.setInt("material.specular", 1);
	//ModelShader.setInt("material.normalMap", 2);
	// 꼭 필요해 각 맵에 접근하려면
	ShaderManager::Instance()->SetUniformModel("ModelShader", pointLightPositions, *m_camera);
	ShaderManager::Instance()->SetUniformModel("ModelShader_geometry", pointLightPositions,*m_camera);
}

void practiceScene::Exit()
{
	delete m_camera;

	for (auto& obj : m_objects)
	{
		delete obj;
	}

}

void practiceScene::Update()
{
	if (KEY_TAP(KEY::ESC))
	{
		exit(0);
	}
	if (KEY_TAP(KEY::F2))
	{
		m_pyramid->SetCount(++count);
		m_pyramid->Sierpinsky();
	}
	m_camera->Move();
	for (auto& obj : m_objects)
	{
		obj->Update();
	}
	m_pyramid->Update();
	for (int i = 0; i < 4; i++)
	{
		pointLightPositions[i] = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::vec4(pointLightPositions[i], 1.0);
	}
}

void practiceScene::Render()
{
	m_frameBuffer.Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	auto shader = ShaderManager::Instance()->GetShader("ModelShader");
	auto projection = m_camera->GetPerspectiveMatrix();
	auto view = m_camera->GetViewMatrix();
	shader.Use();
	shader.setVec3("viewPos", m_camera->GetPosition());
	shader.setVec3("spotLight.position", m_camera->GetPosition());
	shader.setVec3("spotLight.direction", m_camera->GetFront());
	shader.setBool("blinn", blinn);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setVec3("pointLights[0].position", pointLightPositions[0]);
	shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	shader.setVec3("pointLights[2].position", pointLightPositions[2]);
	shader.setVec3("pointLights[3].position", pointLightPositions[3]);
	for (auto& obj : m_objects)
	{
		obj->Draw(shader);
	}
	m_pyramid->Draw(shader);
	
	

	/*shader.setMat4("model", glm::rotate(glm::mat4(1.0f),glm::radians(90.0f),glm::vec3(1.0f,0.f,0.f)));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("brick_wall"));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("brick_wall_normal"));
	renderQuad();// 노멀 맵 테스트용 쿼드
	glBindTexture(GL_TEXTURE_2D, 0);*/


	Shader lightCubeShader = ShaderManager::Instance()->GetShader("lightCubeShader");
	lightCubeShader.Use();//조명의 위치를 보여주기위한 큐브들을 위한 쉐이더(모든색이 하얀색으로 설정됨)
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
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
	m_frameBuffer.Render();
	glutSwapBuffers();
}

void practiceScene::mouse_motion(int x, int y)
{
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	m_camera->ProcessMouseMovement(xoffset, yoffset);

	// 마우스를 중앙으로 이동
	
	glutWarpPointer(centerX, centerY);

	// 중앙으로 이동한 후의 위치를 lastX, lastY로 설정
	lastX = static_cast<float>(centerX);
	lastY = static_cast<float>(centerY);

}

void practiceScene::Mouse(int button, int state, int x, int y)
{
	float xpos = static_cast<float>(x);
	float ypos = static_cast<float>(y);
	CollisionManager::Instance()->Mouse(button, state, x, y, *m_camera);
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

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