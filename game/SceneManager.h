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

	template <typename T>
	void CurrentSceneAddObject()
	{
		m_CurrScene->AddObject<T>();
	}
	template<typename T>
	void CurrentSceneDeleteObject(T* obj)
	{
		m_CurrScene->DeleteObject(obj);
	}
	template<typename T>
	void CurrentSceneDeleteDeleteObject(T* obj)
	{
		m_CurrScene->DeleteDeleteObject(obj);
	}
private:
	Scene* m_CurrScene = nullptr;
	
};



