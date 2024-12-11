#pragma once
#include "object.h"

class Sun : public object 
{
public:
	Sun();
	~Sun() override;
	void Init() override;
	void Init(const string& name) override;
	void Update() override;
	void Draw(Shader& shader) override;

	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;
};
