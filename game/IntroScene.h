#pragma once
#include "Scene.h"

class FrameBuffer;

class  IntroScene : public Scene
{
	std::unique_ptr<FrameBuffer> m_frameBuffer;

	bool firstMouse = true;
	float lastX = 400, lastY = 400;

	bool render = false;
public:
	IntroScene();
	~IntroScene();

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
	void mouse_motion(int x, int y) override;
	void Mouse(int button, int state, int x, int y) override;
	void mouse_wheel(int button, int dir, int x, int y) override;
};
