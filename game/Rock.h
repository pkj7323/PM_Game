#pragma once
#include "object.h"
#include "Model.h"
class SpaceShip;
class Shader;
enum class Type { Normal, Spin, };
class Rock : public object
{
	Type type{};
	
	float speed = 10.f;
	glm::vec3 direction{};
	std::uniform_real_distribution<float> randPos{ -50.f, 50.f };
	std::uniform_real_distribution<float> randSpeed{ 10.f, 30.f };
	std::uniform_int_distribution<int> randType{0 , 1};


	glm::mat4 m_mat_r = glm::mat4(1.0f);
	glm::mat4 m_mat_t = glm::mat4(1.0f);
	glm::vec3 m_pos{};

	float m_rotate{};
	float radius{};
public:
	Rock();
	~Rock() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;

	void SetDirection(const SpaceShip& spaceship);
};
