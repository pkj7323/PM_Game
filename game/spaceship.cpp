#include "stdafx.h"
#include "SpaceShip.h"
#include "KeyManager.h"
#include "Camera.h"
#include "CollisionManager.h"
#include "TextureLoadManager.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "SoundManager.h"
#include "TimeManager.h"

SpaceShip::SpaceShip() : object("space_ship")
{
	bs.radius = 2.0f;
	CollisionManager::Instance()->AddObject("SpaceShip:Rock", this, nullptr);
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::Init()
{
	object::Init();
}

void SpaceShip::Init(const string& name)
{
	object::Init(name);
}

void SpaceShip::Update()
{
	if (KEY_HOLD(KEY::A)) {
		if (rotation.z < 45) {
			rotation.z += 0.5f;
		}
	}
	else {
		if (rotation.z > 0) {
			rotation.z -= 0.5f;
		}
	}
	if (KEY_HOLD(KEY::D)) {
		if (rotation.z > -45) {
			rotation.z -= 0.5f;
		}
	}
	else {
		if (rotation.z < 0) {
			rotation.z += 0.5f;
		}
	}
	if (KEY_TAP(KEY::F1))
	{
		if (bool_TP_to_FP)
		{
			up_parm = FP_UP;
			front_parm = FP_FRONT;
		}
		else
		{
			up_parm = TP_UP;
			front_parm = TP_FRONT;
		}
		bool_TP_to_FP = !bool_TP_to_FP;
	}
	if (KEY_TAP(KEY::R))
	{
		if (is_roll == false) {
			is_roll = true;
		}
	}
	if (is_hit){

		
		hit_time += DT;
		if (hit_time > Hit_Spanning_Time)
		{
			is_hit = false;
		}
		Shaking();
	}

	Barrel_Roll();
	
	
	object::Update();
}

void SpaceShip::Draw(Shader& shader,const Camera& c)
{
	object::Draw(shader);
	if (is_fire)
	{
		RenderBillBoardRect(c);

		if (m_rayDes != glm::vec3{0,0,0})
		{

			auto model = glm::mat4(1.0f);
			float vertices[] = {
				GetLightPos3().x, GetLightPos3().y, GetLightPos3().z,
				m_rayDes.x, m_rayDes.y, m_rayDes.z
			};
			unsigned int VAO, VBO;
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);

			// VAO 바인드
			glBindVertexArray(VAO);

			// VBO 바인드 및 데이터 전달
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// 3. 좌표 속성 설정
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			shader = ShaderManager::Instance()->GetShader("LightCubeShader");
			shader.Use();
			shader.setMat4("model", model);
			shader.setMat4("view", c.GetViewMatrix());
			shader.setMat4("projection", c.GetPerspectiveMatrix());
			glBindVertexArray(VAO);
			glDrawArrays(GL_LINE_STRIP, 0, 2);

			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
		timer += DT;
		if (timer > 0.1f)
		{
			timer = 0.f;
			m_rayDes = { 0,0,0 };
			is_fire = false;
		}
	}
}



glm::vec3 SpaceShip::GetLightPos1() const
{
	glm::vec3 lightPos(0.0f);
	lightPos.x = -0.5f;
	lightPos.z = 1.5f;
	glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	r = glm::rotate(r, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	r = glm::rotate(r, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	lightPos = glm::vec3(r * glm::vec4(lightPos, 1.0f));
	lightPos = glm::vec3(t * glm::vec4(lightPos, 1.0f));
	
	return lightPos;
}

glm::vec3 SpaceShip::GetLightPos2() const
{
	glm::vec3 lightPos(0.0f);
	lightPos.x = 0.5f;
	lightPos.z = 1.5f;
	glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	r = glm::rotate(r, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	r = glm::rotate(r, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	lightPos = glm::vec3(r * glm::vec4(lightPos, 1.0f));
	lightPos = glm::vec3(t * glm::vec4(lightPos, 1.0f));

	
	
	return lightPos;
}

glm::vec3 SpaceShip::GetLightPos3() const
{
	glm::vec3 lightPos(0.0f);
	lightPos.x = 0.0f;
	lightPos.y = 0.2f;
	lightPos.z = -2.3f;
	glm::mat4 t = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	r = glm::rotate(r, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	r = glm::rotate(r, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	lightPos = glm::vec3(r * glm::vec4(lightPos, 1.0f));
	lightPos = glm::vec3(t * glm::vec4(lightPos, 1.0f));

	return lightPos;
}

void SpaceShip::ProcessMouseMovement(const Camera& camera)
{
	rotation.x = camera.GetPitch();
	rotation.y = -(camera.GetYaw() + 90);
	this->Move(camera);

	object::Update();
}

void SpaceShip::RenderBillBoardRect(const Camera& camera)
{
	// 카메라의 Right와 Up 벡터를 사용하여 빌보드의 네 모서리 위치를 계산합니다.
	glm::vec3 right = glm::normalize(glm::cross(camera.GetFront(), glm::vec3(0,1,0))) * glm::vec3(1.0f) * 0.5f;
	glm::vec3 up = glm::normalize(glm::cross(right, camera.GetFront())) * glm::vec3(1.0f) * 0.5f;

	auto billboardPosition = GetLightPos3();

	glm::vec3 topLeft = billboardPosition - right + up;
	glm::vec3 topRight = billboardPosition + right + up;
	glm::vec3 bottomLeft = billboardPosition - right - up;
	glm::vec3 bottomRight = billboardPosition + right - up;

	// 빌보드 사각형의 정점 데이터를 설정합니다.
	float vertices[] = {
		// positions          // texture coords
		topLeft.x, topLeft.y, topLeft.z, 0.0f, 1.0f,
		bottomLeft.x, bottomLeft.y, bottomLeft.z, 0.0f, 0.0f,
		bottomRight.x, bottomRight.y, bottomRight.z, 1.0f, 0.0f,

		topLeft.x, topLeft.y, topLeft.z, 0.0f, 1.0f,
		bottomRight.x, bottomRight.y, bottomRight.z, 1.0f, 0.0f,
		topRight.x, topRight.y, topRight.z, 1.0f, 1.0f
	};

	// VAO와 VBO를 생성하고 설정합니다.
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);

	auto shader = ShaderManager::Instance()->GetShader("PlanetShader");
	shader.Use();
	shader.setMat4("view", camera.GetViewMatrix());
	shader.setMat4("projection", camera.GetPerspectiveMatrix());
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, GetLightPos3());
	//model = glm::scale(model, glm::vec3(0.5f));
	shader.setMat4("model", model);
	TextureLoadManager::Instance()->Unbind(2);
	TextureLoadManager::Instance()->Use("laser_effect");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 빌보드 사각형을 렌더링합니다.
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
	TextureLoadManager::Instance()->Unbind(0);
	

	// VAO와 VBO를 정리합니다.
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SpaceShip::Shaking()
{
	if (is_shake) {
		if (shake_cnt < 16) {
			right_shake = randPos(math::dre);
			up_shake = randPos(math::dre);
			front_shake = randPos(math::dre);
			shake_cnt++;
		}
		else {
			is_shake = false;
			up_shake = 0;
			front_shake = 0;
			right_shake = 0;
		}
	}
}

void SpaceShip::Barrel_Roll()
{
	if (is_roll) {
		if (rotation.z < 0) {
			if (rotation.z > -720) {
				angularVelocity -= angularAcceleration; // 가속도 반영하여 각속도 증가
				rotation.z += angularVelocity; // 각속도 반영하여 각도 업데이트
			}
			else {
				is_roll = false;
				rotation.z = 0;
				angularVelocity = 3.f; // 각속도 초기화
			}
		}
		else {
			if (rotation.z < 720) {
				angularVelocity += angularAcceleration; // 가속도 반영하여 각속도 증가
				rotation.z += angularVelocity; // 각속도 반영하여 각도 업데이트
			}
			else {
				is_roll = false;
				rotation.z = 0;
				angularVelocity = 3.f; // 각속도 초기화
			}
		}
	}
}


void SpaceShip::OnCollision(const string& group, object* other)
{
	if (group == "SpaceShip:Rock")
	{
		if (!is_hit && !is_roll)
		{
			is_hit = true;
			hit_time = 0.0f;
			Life -= 1.f;
			if (is_shake == false) {
				is_shake = true;
				shake_cnt = 0;
			}
			SoundManager::Instance()->Play("damage_sound");
			cout << Life << endl;
		}
	}
}

void SpaceShip::OnCollisionEnd(const string& group, object* other)
{

}

void SpaceShip::MouseClick()
{
	if (!is_fire)
	{
		is_fire = true;
	}
}

void SpaceShip::Move(const Camera& camera)
{
	auto position = camera.GetPosition();
	auto up = camera.GetUp();
	auto front = camera.GetFront();
	auto right = camera.GetRight();
	position -= up * up_parm;
	position += front * front_parm;
	position += up * up_shake;
	position += front * front_shake;
	position += right * right_shake;
	pos = position;
}
