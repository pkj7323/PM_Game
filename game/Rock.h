#pragma once
#include "object.h"
#include "Model.h"


class Shader;
class SpaceShip;
class Rock : public object
{
	float speed = 10.f;

	glm::vec3 direction{};
	std::uniform_real_distribution<float> randPos{ -50.f, 50.f };
	std::uniform_real_distribution<float> randSpeed{ 10.f, 30.f };
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
