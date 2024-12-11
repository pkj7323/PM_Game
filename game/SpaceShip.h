#pragma once
#include "ModelManager.h"
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
	void Draw(Shader& shader,const Camera& camera);

	void OnCollision(const string& group, object* other) override;
	void OnCollisionEnd(const string& group, object* other) override;

	void MouseClick();

	void Move(const Camera& camera);
	glm::vec3 GetLightPos1() const;
	glm::vec3 GetLightPos2() const;
	glm::vec3 GetLightPos3() const;
	glm::vec3& GetRayDes() { return m_rayDes; };
	void ProcessMouseMovement(const Camera& camera);

	void RenderBillBoardRect(const Camera& camera);

private:
	Model laser_effect = ModelManager::Instance()->GetModel("cube");
	float up_parm = 2.f;
	float front_parm = 2.5f;
	bool bool_TP_to_FP = true;
	bool is_fire = false;
	float Timer = 0.0;

	glm::vec3 m_rayDes;
};
