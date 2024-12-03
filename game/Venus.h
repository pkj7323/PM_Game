#pragma once
#include "object.h"
class Venus :
    public object
{
public:
	Venus();
	~Venus() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;
};

