#pragma once
#include "Camera.h"
#include "FrameBuffer.h"
#include "Scene.h"
#include "Model.h"
#include "SkyBox.h"

class SpaceShip;
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
	std::uniform_real_distribution<float> randomFloats{ 0.0, 1.0 };
	Camera* m_camera;
	bool firstMouse = true;
	float last_x_ = glutGet(GLUT_WINDOW_WIDTH) / 2;
	float last_y_ = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	const int center_x_ = glutGet(GLUT_WINDOW_WIDTH) / 2;
	const int center_y_ = glutGet(GLUT_WINDOW_HEIGHT) / 2;

	Model m_cube;//임시 조명 위치용
	Model m_model;//임시 객체 테스트용
	Model m_sphere;// 임시 구체 테스트용
	//Pyramid* m_pyramid;
	vector<Cube*> cubes;
	SkyBox m_skyBox;




	glm::vec3 ambient_light{ 0.05,0.05,0.05 };
	glm::vec3 specular_light{ 1.0f,1.0f,1.0f };

	SpaceShip* m_space_ship;
	FrameBuffer m_frameBuffer;
	vector<glm::vec3> pointLightPositions;


	vector<object*> m_objects;

	bool blinn = true;

	unsigned int quadVAO = 0;
	unsigned int quadVBO;
};
