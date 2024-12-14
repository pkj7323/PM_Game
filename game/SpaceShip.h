#pragma once
#include "ModelManager.h"
#include "object.h"

#define Hit_Spanning_Time 1.0f

#define FP_UP 0.f
#define FP_FRONT 0.f

#define TP_UP 3.f
#define TP_FRONT 8.0f
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
	glm::vec3 GetPos() const { return pos; }
	glm::vec3 GetLightPos1() const;
	glm::vec3 GetLightPos2() const;
	glm::vec3 GetLightPos3() const;
	glm::vec3& GetRayDes() { return m_rayDes; };
	bool GetisRoll() const { return is_roll; };
	void ProcessMouseMovement(const Camera& camera);

	void RenderBillBoardRect(const Camera& camera);

	void Shaking();
	void Barrel_Roll();

	float GetLife() const { return Life; }
private:

	std::uniform_real_distribution<float> randPos{ -0.4f, 0.4f };

	glm::vec3 startPos{};
	Model laser_effect = ModelManager::Instance()->GetModel("cube");
	float up_parm = 3.f;
	float front_parm = 8.0f;
	bool bool_TP_to_FP = true;
	bool is_fire = false;
	bool is_roll = false;
	bool is_shake = false;
	float Timer = 0.0;

    float hit_time = 0.0f;
	bool is_hit = false;
	
	float angularVelocity = 1.0f; // 초기 각속도
	float angularAcceleration = 0.2f; // 각가속도 (가속도 크기는 상황에 따라 조정)

	
	int shake_cnt{};
	float up_shake{};
	float front_shake{};
	float right_shake{};


	float Life = 10.f;
	glm::vec3 m_rayDes;
};
