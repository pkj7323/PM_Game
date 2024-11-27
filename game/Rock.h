#pragma once
#include "object.h"
#include "Model.h"
class Shader;
class Rock : public object
{
	Model m_Rock;
public:
	Rock();
	~Rock() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;
	AABB GetBB() override;
};
