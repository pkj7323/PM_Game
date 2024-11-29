#pragma once
#include "Scene.h"

class SceneManager
{

	SINGLE(SceneManager)
public:
	void Init();
	void Update();
    template <typename T, typename = std::enable_if_t<std::is_base_of_v<Scene, T>>>
	void Enter();
	void Render();
	void Release();
	Scene* GetCurrScene() { return m_CurrScene; }
	void mouse_motion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void mouse_wheel(int button, int dir, int x, int y);

private:
	Scene* m_CurrScene = nullptr;
	
};

template <typename T, typename>
void SceneManager::Enter()
{
	if (m_CurrScene != nullptr)
	{
		m_CurrScene->Exit();
		delete m_CurrScene;
	}
	m_CurrScene = new T;
	m_CurrScene->Enter();
}

