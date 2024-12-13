#pragma once
#include "Scene.h"

class endingScene : public Scene
{
public:
	endingScene();
	~endingScene() override;
	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
	void mouse_motion(int x, int y) override;
	void Mouse(int button, int state, int x, int y) override;
	void mouse_wheel(int button, int dir, int x, int y) override;
};
