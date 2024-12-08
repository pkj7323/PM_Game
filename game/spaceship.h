#pragma once
#include "object.h"

class Spaceship : public object
{
	
public:
	Spaceship();
	~Spaceship() override;
	void Init() override;
	void Update() override;
	void Draw(Shader& shader) override;
	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;



	void Move(glm::vec3 position, glm::vec3 up, glm::vec3 front);
	void Rotate_y(float pitch);
	void Rotate_x(float yat);


};

