#pragma once
#include "CameraManager.h"
#include "Scene.h"
class Model;
class practiceScene : public Scene
{
public:
	practiceScene();
	~practiceScene();

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
	void mouse_motion(int x, int y) override;
	void Mouse(int button, int state, int x, int y) override;
	void mouse_wheel(int button, int dir, int x, int y) override;
private:
	CameraManager* m_camera;
	bool firstMouse = true;
	float lastX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float lastY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	const int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	const int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	Model* m_model;
	float timer = 0;
	vector<glm::vec3> pointLightPositions;
	glm::vec3 pointLightColor;
};
