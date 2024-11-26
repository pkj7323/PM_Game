#pragma once

class Scene;
class SceneManager
{

	SINGLE(SceneManager)
public:
	void Init();
	void Update();
	void Render();

	Scene* GetCurrScene() { return m_CurrScene; }
private:
	Scene* arrScene[static_cast<UINT>(SCENE_TYPE::END)];
	Scene* m_CurrScene = nullptr;
	
};

