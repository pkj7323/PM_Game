#include "stdafx.h"
#include "IntroScene.h"
#include "Camera.h"
#include "Core.h"
#include "KeyManager.h"
#include "Model.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureLoadManager.h"
#include "FrameBuffer.h"
#include "practiceScene.h"
#include "SceneManager.h"


IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::Enter()
{
   
	m_frameBuffer = std::make_unique<FrameBuffer>();
    
	
}

void IntroScene::Exit()
{

}

void IntroScene::Update()
{
	if (KEY_TAP(KEY::ESC))
	{
		Core::Instance()->Release();
	}
	if (render)
	{
		TextureLoadManager::Instance()->TexturesLoad();
		ModelManager::Instance()->ModelLoad();
		SceneManager::Instance()->Enter<practiceScene>();
	}
	

}

void IntroScene::Render()
{
	m_frameBuffer->Bind();
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	auto shader = ShaderManager::Instance()->GetShader("BasicShader");
	shader.Use();
	glm::mat4 model{ 1.0f };
	//model = glm::rotate(model, glm::radians(180.f), glm::vec3(0, 0, 1));
	shader.setMat4("model", model);
	shader.setMat4("view", glm::mat4(1.0f));
	shader.setMat4("projection", glm::mat4(1.0f));
	shader.setInt("texture1", 0);
	TextureLoadManager::Instance()->Use("TUK");
	renderQuad();
	TextureLoadManager::Instance()->Unbind();

	m_frameBuffer->Render();
	glutSwapBuffers();
	render = true;
}

void IntroScene::mouse_motion(int x, int y)
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

	

	// 마우스를 중앙으로 이동
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(centerX, centerY);

	// 중앙으로 이동한 후의 위치를 lastX, lastY로 설정
	lastX = static_cast<float>(centerX);
	lastY = static_cast<float>(centerY);

}

void IntroScene::Mouse(int button, int state, int x, int y)
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

	
}

void IntroScene::mouse_wheel(int button, int dir, int x, int y)
{
	
	
}
