#pragma once
#include "object.h"

class Camera;
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


	void Move(const Camera& camera);
	glm::vec3 GetLightPos1() const;
	glm::vec3 GetLightPos2() const;
	glm::vec3 GetLightPos3() const;
	
	void ProcessMouseMovement(const Camera& camera);

	glm::vec3 GetPosition() const { return pos; }


private:
	float up_parm = 2.f;
	float front_parm = 2.5f;
	bool bool_TP_to_FP = true;
};
