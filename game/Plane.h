#pragma once
#include "object.h"

class Plane : public object
{
public:
	Plane();
	~Plane() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;
	
};
