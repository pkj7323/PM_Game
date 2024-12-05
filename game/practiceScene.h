#pragma once
#include "Camera.h"
#include "FrameBuffer.h"
#include "Scene.h"
#include "Model.h"
#include "SkyBox.h"

class Cube;
class Pyramid;

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

	void renderQuad();

private:
	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_real_distribution<float> randomFloats{ 0.0, 1.0 };
	Camera* m_camera;
	bool firstMouse = true;
	float lastX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float lastY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	const int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	const int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	Model m_cube;
	Model m_model;
	Model m_sphere;
	Pyramid* m_pyramid;
	vector<Cube*> cubes;
	SkyBox m_skyBox;
	vector<string> m_textures;
	glm::mat4 matrix{1.0f};
	int index = 0;

	int count = 0;
	bool light_rotation = false;
	bool light_on = true;
	bool do_update = true;

	glm::vec3 ambient_light{ 0.05,0.05,0.05 };
	glm::vec3 specular_light{ 1.0f,1.0f,1.0f };
	glm::vec3 pointLightColor;

	FrameBuffer m_frameBuffer;
	vector<glm::vec3> pointLightPositions;
	
	unsigned int amount = 1000;
	glm::mat4* modelMatrices;

	vector<object*> m_objects;

	bool blinn = false;

	unsigned int quadVAO = 0;
	unsigned int quadVBO;
};
