#include "stdafx.h"
#include "practiceScene.h"
#include "Model.h"
#include "KeyManager.h"
#include "ShaderManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "ModelManager.h"
#include "TextureLoadManager.h"
#include "TimeManager.h"
#include "rock.h"


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
	//TextureLoadManager::Instance()->Load("rock", "resources/rock/rock.png");
	
	m_objects.push_back(new Rock);

	m_model = ModelManager::Instance()->GetModel("backpack");
	m_planet = ModelManager::Instance()->GetModel("earth");

	TextureLoadManager::Instance()->Load("diffuseWall", "resources/brick/brickwall.jpg");
	TextureLoadManager::Instance()->Load("normalWall", "resources/brick/brickwall_normal.jpg");

	modelMatrices = new glm::mat4[amount];
	srand(static_cast<unsigned int>(glutGet(GLUT_ELAPSED_TIME)/1000)); // initialize random seed
	float radius = 150.0;
	float offset = 25.5f;
	for (unsigned int i = 0; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. scale: Scale between 0.05 and 0.25f
		float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
		model = glm::scale(model, glm::vec3(scale));

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = static_cast<float>((rand() % 360));
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. now add to list of matrices
		modelMatrices[i] = model;
	}
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0; i < m_model.meshes.size(); i++)
	{
		unsigned int VAO = m_model.meshes[i].VAO;
		glBindVertexArray(VAO);
		// vertex attributes
		std::size_t vec4Size = sizeof(glm::vec4);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

		glVertexAttribDivisor(3, 1);
		glVertexAttribDivisor(4, 1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);
	}
	Shader ModelShader = ShaderManager::Instance()->GetShader("ModelShader");
	ModelShader.Use();
	ModelShader.setVec3("PointLightPos[0]", pointLightPositions[0]);
	ModelShader.setVec3("PointLightPos[1]", pointLightPositions[1]);
	ModelShader.setVec3("PointLightPos[2]", pointLightPositions[2]);
	ModelShader.setVec3("PointLightPos[3]", pointLightPositions[3]);


	ModelShader.setFloat("material.shininess", 32.0f);

	ModelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	ModelShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	ModelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	//포인트 라이트의 위치
	ModelShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);//포인트 라이트의 주변광
	ModelShader.setVec3("pointLights[0].diffuse", pointLightColor);//포인트 라이트의 확산광
	ModelShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);//포인트 라이트의 반사광
	ModelShader.setFloat("pointLights[0].constant", 1.0f);//포인트 라이트의 상수값
	ModelShader.setFloat("pointLights[0].linear", 0.09);//포인트 라이트의 선형값(1차)
	ModelShader.setFloat("pointLights[0].quadratic", 0.032);//포인트 라이트의 이차값(2차)

	
	ModelShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[1].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[1].constant", 1.0f);
	ModelShader.setFloat("pointLights[1].linear", 0.09f);
	ModelShader.setFloat("pointLights[1].quadratic", 0.032f);


	ModelShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[2].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[2].constant", 1.0f);
	ModelShader.setFloat("pointLights[2].linear", 0.09f);
	ModelShader.setFloat("pointLights[2].quadratic", 0.032f);

	
	ModelShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	ModelShader.setVec3("pointLights[3].diffuse", pointLightColor);
	ModelShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("pointLights[3].constant", 1.0f);
	ModelShader.setFloat("pointLights[3].linear", 0.09f);
	ModelShader.setFloat("pointLights[3].quadratic", 0.032f);

	ModelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	ModelShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	ModelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	ModelShader.setFloat("spotLight.constant", 1.0f);
	ModelShader.setFloat("spotLight.linear", 0.09f);
	ModelShader.setFloat("spotLight.quadratic", 0.032f);
	ModelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	//손전등의 안쪽조명을 받을 각도
	ModelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}

void practiceScene::Exit()
{
	delete m_camera;

	

}

void practiceScene::Update()
{
	if (KEY_TAP(KEY::ESC))
	{
		exit(0);
	}
	if (KEY_TAP(KEY::F1))
	{
		glEnable(GL_FRAMEBUFFER_SRGB);
	}
	if (KEY_TAP(KEY::F2))
	{
		glDisable(GL_FRAMEBUFFER_SRGB);
	}
	if (KEY_TAP(KEY::F3))
	{
		Shader ModelShader = ShaderManager::Instance()->GetShader("ModelShader");
		ModelShader.Use();
		blinn = !blinn;
		ModelShader.setBool("blinn", blinn);
	}
	m_camera->Move();
	pointLightPositions[0] = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), glm::vec3(0, 1, 0)) * glm::vec4(pointLightPositions[0],1.0);
	for (auto& obj : m_objects)
	{
		obj->Update();
	}
}

void practiceScene::Render()
{
	m_frameBuffer.Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader shader = ShaderManager::Instance()->GetShader("PlanetShader");
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_camera->GetViewMatrix();
	glm::mat4 projection = m_camera->GetPerspectiveMatrix();

	/*shader.Use();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 10.0f, -100.0f));
	shader.setMat4("model", model);

	m_planet.Draw(shader);*/

	/*Shader ModelShader = ShaderManager::Instance()->GetShader("ModelShader");
	ModelShader.Use();
	ModelShader.setMat4("projection", projection);
	ModelShader.setMat4("view", view);
	ModelShader.setVec3("viewPos", m_camera->GetPosition());
	ModelShader.setVec3("PointLightPos[0]", pointLightPositions[0]);
	ModelShader.setVec3("PointLightPos[1]", pointLightPositions[1]);
	ModelShader.setVec3("PointLightPos[2]", pointLightPositions[2]);
	ModelShader.setVec3("PointLightPos[3]", pointLightPositions[3]);
	ModelShader.setVec3("SpotLightPos", m_camera->GetPosition());
	ModelShader.setVec3("spotLight.direction", m_camera->GetFront());*/
	
	shader = ShaderManager::Instance()->GetShader("NormalMapShader");
	shader.Use();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	

	// configure view/projection matrices


	// render normal-mapped quad
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::normalize(glm::vec3(1.0, 0.0, 0.0))); // rotate the quad to show normal mapping from multiple directions
	shader.setMat4("model", model);
	shader.setVec3("viewPos", m_camera->GetPosition());
	shader.setVec3("lightPos", pointLightPositions[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("diffuseWall"));
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("normalWall"));
	renderQuad();




	for (auto& obj : m_objects)
	{
		obj->Draw(shader);
	}
	model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.02, 0.02, 0.02));
	shader.setMat4("model",model);
	m_planet.Draw(shader);
	m_model.Draw(shader);

	Shader lightCubeShader = ShaderManager::Instance()->GetShader("lightCubeShader");
	lightCubeShader.Use();//조명의 위치를 보여주기위한 큐브들을 위한 쉐이더(모든색이 하얀색으로 설정됨)
	lightCubeShader.setMat4("projection", projection);
	lightCubeShader.setMat4("view", view);
	// render the cube
	for (int i = 0; i < 1; i++)
	{
		model = glm::mat4(1.0f);
		model = glm::translate(model, pointLightPositions[i]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//스케일이 먼저 적용
		lightCubeShader.setMat4("model", model);
		auto cube = ModelManager::Instance()->GetModel("cube");
		cube.Draw(lightCubeShader);
	}
	/*shader = ShaderManager::Instance()->GetShader("asteroidShader");
	shader.Use();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	shader.setInt("texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_model.textures_loaded[0].id);
	for (unsigned int i = 0; i < m_model.meshes.size(); i++)
	{
		glBindVertexArray(m_model.meshes[i].VAO);
		glDrawElementsInstanced(
			GL_TRIANGLES, m_model.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount
		);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);*/


	
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