#include "stdafx.h"
#include "endingScene.h"
#include "FrameBuffer.h"
#include "Core.h"
#include "KeyManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "TextureLoadManager.h"

endingScene::endingScene()
{
}

endingScene::~endingScene()
{
}

void endingScene::Enter()
{
	SoundManager::Instance()->Stop("bgm");
	SoundManager::Instance()->Stop("laser_effect");
	SoundManager::Instance()->Stop("explosion_effect");
	SoundManager::Instance()->Stop("spaceship_sfx");

	SoundManager::Instance()->Play("ending");

	m_frameBuffer = std::make_unique<FrameBuffer>();
	glutSetCursor(GLUT_CURSOR_INHERIT); // 커서를 나타내는 모드로 설정
}

void endingScene::Exit()
{
}

void endingScene::Update()
{
	if (KEY_TAP(KEY::ESC))
	{
		Core::Instance()->Release();
	}
	
}

void endingScene::Render()
{
	m_frameBuffer->Bind();

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//배경을 0.1,0.1,0.1로 설정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	auto shader = ShaderManager::Instance()->GetShader("BasicShader");
	shader.Use();
	shader.setMat4("projection",glm::mat4(1.0f));
	shader.setMat4("view",glm::mat4(1.0f));
	shader.setMat4("model",glm::mat4(1.0f));
	shader.setInt("texture1", 0);
	TextureLoadManager::Instance()->Use("ending");
	Scene::renderQuad();
	TextureLoadManager::Instance()->Unbind(0);

	m_frameBuffer->Render();
	glutSwapBuffers();
}

void endingScene::mouse_motion(int x, int y)
{
}

void endingScene::Mouse(int button, int state, int x, int y)
{
}

void endingScene::mouse_wheel(int button, int dir, int x, int y)
{
}
