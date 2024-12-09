#pragma once
#include "object.h"
#include "practiceScene.h"

class SpaceShip:public object
{
public:
	SpaceShip();
	~SpaceShip() override;
	void Init() override;
	void Init(const string& name) override;
	void Update() override;
	void Draw(Shader& shader) override;

	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;


	void Move(glm::vec3 position, glm::vec3 up, glm::vec3 front);
	glm::vec3 GetLightPos1() const;
	glm::vec3 GetLightPos2() const;
	
	void ProcessMouseMovement(const Camera& camera);

private:
};
