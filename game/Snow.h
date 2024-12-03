#pragma once
#include "object.h"

class Snow : public object
{
	float speed = 10.f;
	std::default_random_engine dre{ std::random_device{}() };
	std::uniform_real_distribution<float> randPos{ -25.f, 25.f };
	std::uniform_real_distribution<float> randSpeed{ 10.f, 30.f };
public:
	Snow();
	~Snow() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;
};
