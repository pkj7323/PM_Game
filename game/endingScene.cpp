#include "stdafx.h"
#include "endingScene.h"

#include "Core.h"
#include "KeyManager.h"
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
	SoundManager::Instance()->Play("ending");
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
	TextureLoadManager::Instance()->Use("ending");
	Scene::renderQuad();
	TextureLoadManager::Instance()->Unbind(0);
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
