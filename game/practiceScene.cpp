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

	Shader shader = ShaderManager::Instance()->GetShader("geoShader");
	shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_camera->GetViewMatrix();
	glm::mat4 projection = m_camera->GetPerspectiveMatrix();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	timer += DT;
	shader.setFloat("time", static_cast<float>(timer));

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
