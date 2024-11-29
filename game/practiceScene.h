#pragma once
#include "Camera.h"
#include "FrameBuffer.h"
#include "Scene.h"
#include "Model.h"

class practiceScene : public Scene
{
public:
	practiceScene();
	~practiceScene() override;

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
	void mouse_motion(int x, int y) override;
	void Mouse(int button, int state, int x, int y) override;
	void mouse_wheel(int button, int dir, int x, int y) override;
private:
	Camera* m_camera;
	bool firstMouse = true;
	float lastX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float lastY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	const int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	const int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	Model m_model;
	Model m_planet;
	FrameBuffer m_frameBuffer;
	vector<glm::vec3> pointLightPositions;
	glm::vec3 pointLightColor;
	unsigned int amount = 1000;
	glm::mat4* modelMatrices;

	vector<object*> m_objects;

	bool blinn = false;
};
