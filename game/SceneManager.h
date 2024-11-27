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
	void mouse_motion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void mouse_wheel(int button, int dir, int x, int y);

private:
	vector<Scene*> arrScene;
	Scene* m_CurrScene = nullptr;
	
};

