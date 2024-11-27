#pragma once
#include "Scene.h"

class  IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
	void mouse_motion(int x, int y) override;
	void Mouse(int button, int state, int x, int y) override;
};
