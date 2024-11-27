#include "stdafx.h"
#include "practiceScene.h"

#include "ShaderManager.h"

practiceScene::practiceScene()
{
}

practiceScene::~practiceScene()
{
}

void practiceScene::Enter()
{
	m_camera = new CameraManager;
	ShaderManager::Instance()->MakeShader()
}

void practiceScene::Exit()
{
}

void practiceScene::Update()
{
}

void practiceScene::Render()
{
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
