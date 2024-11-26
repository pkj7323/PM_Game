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
	vector<Scene*> arrScene;
	Scene* m_CurrScene = nullptr;
	
};

