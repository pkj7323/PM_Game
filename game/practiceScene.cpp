#include "stdafx.h"
#include "practiceScene.h"
#include "Model.h"
#include "KeyManager.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "TimeManager.h"
float points[]={
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // top-right
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
};
GLuint VAO, VBO;

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
	m_camera = new CameraManager;
	ShaderManager::Instance()->MakeShader("geoShader",
		"Vertex.glsl", "Fragment.glsl","Geometry.glsl");
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glBindVertexArray(0);

	m_model = new Model("resources/backpack.obj");
}

void practiceScene::Exit()
{
	delete m_camera;
	delete m_model;
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

}

void practiceScene::Update()
{
	if (KEY_TAP(KEY::ESC))
	{
		exit(0);
	}
	m_camera->Move();
}

void practiceScene::Render()

{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader shader = ShaderManager::Instance()->GetShader("ModelShader");
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_camera->GetViewMatrix();
	glm::mat4 projection = m_camera->GetPerspectiveMatrix();
	shader.Use();//이거아래의 그리기 동작들은 모델 쉐이더에 영향을 미친다. 1pass
	shader.setMat4("projection",projection);
	shader.setMat4("view", view);
	shader.setVec3("viewPos", m_camera->GetPosition());
	shader.setFloat("material.shininess", 32.0f);
	// directional light
	// 태양광 설정
	shader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
	shader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

	// point light 1
	// 포인트 라이트 1 설정
	shader.setVec3("pointLights[0].position", pointLightPositions[0]);//포인트 라이트의 위치
	shader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);//포인트 라이트의 주변광
	shader.setVec3("pointLights[0].diffuse", pointLightColor);//포인트 라이트의 확산광
	shader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);//포인트 라이트의 반사광
	shader.setFloat("pointLights[0].constant", 1.0f);//포인트 라이트의 상수값
	shader.setFloat("pointLights[0].linear", 0.09f);//포인트 라이트의 선형값(1차)
	shader.setFloat("pointLights[0].quadratic", 0.032f);//포인트 라이트의 이차값(2차)
	
	shader.setVec3("pointLights[1].position", pointLightPositions[1]);
	shader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[1].diffuse", pointLightColor);
	shader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[1].constant", 1.0f);
	shader.setFloat("pointLights[1].linear", 0.09f);
	shader.setFloat("pointLights[1].quadratic", 0.032f);
	// point light 3
	shader.setVec3("pointLights[2].position", pointLightPositions[2]);
	shader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[2].diffuse", pointLightColor);
	shader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[2].constant", 1.0f);
	shader.setFloat("pointLights[2].linear", 0.09f);
	shader.setFloat("pointLights[2].quadratic", 0.032f);
	// point light 4
	shader.setVec3("pointLights[3].position", pointLightPositions[3]);
	shader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
	shader.setVec3("pointLights[3].diffuse", pointLightColor);
	shader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("pointLights[3].constant", 1.0f);
	shader.setFloat("pointLights[3].linear", 0.09f);
	shader.setFloat("pointLights[3].quadratic", 0.032f);
	// spotLight
	shader.setVec3("spotLight.position", m_camera->GetPosition());
	shader.setVec3("spotLight.direction", m_camera->GetFront());
	shader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
	shader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("spotLight.constant", 1.0f);
	shader.setFloat("spotLight.linear", 0.09f);
	shader.setFloat("spotLight.quadratic", 0.032f);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	//손전등의 안쪽조명을 받을 각도
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	//손전등의 바깥쪽 조명을 받을 각도 <-- 이 각도 사이에 있는 조명을 받는데 줄어들면서 받는다(실감나는 효과).
	shader.setMat4("model", model);
	m_model->Draw(shader);
	shader = ShaderManager::Instance()->GetShader("geoShader");
	shader.Use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
	m_model->Draw(shader);

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
