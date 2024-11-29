#pragma once
#include "Model.h"
#include "Scene.h"

class  IntroScene : public Scene
{
	Model ourModel;
	Model ourCube;
	Model ourPlane;
	Model ourPyramid;
	Model ourSphere;

	bool blinn = false;
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
