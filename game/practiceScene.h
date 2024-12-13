#pragma once
#include "Camera.h"
#include "Scene.h"
#include "Model.h"


class Sun;
class SkyBox;
class Sound;
class SpaceShip;
class Cube;
class FrameBuffer;
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
	void RenderCrosshair(const Camera& camera);

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


	SkyBox* m_skyBox;

	Sun* sun;


	glm::vec3 sun_ambient{ 0.05f,0.05f,0.05f };
	glm::vec3 sun_diffuse{ 10.0f,10.0f,10.0f };
	glm::vec3 sun_specular{ 1.0f,1.0f,1.0f };

	SpaceShip* m_space_ship;
	FrameBuffer* m_frameBuffer;
	vector<glm::vec3> pointLightPositions;


	bool blinn = false;

	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	float time = 0;
};
