#pragma once
#include "object.h"

class Pyramid : public object
{
	UINT count = 0;
public:
	Pyramid();
	~Pyramid() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;
	void SetCount(UINT count) { this->count = count; }
	void Sierpinsky();
};
