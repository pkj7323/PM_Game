#include "stdafx.h"
#include "SpaceShip.h"
#include "KeyManager.h"
#include "Camera.h"
#include "TextureLoadManager.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "TimeManager.h"

SpaceShip::SpaceShip() : object("space_ship")
{
	bs.center.y += 1.0f;
	bs.radius = 2.0f;
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
			up_parm = 0.f;
			front_parm = 0.f;
		}
		else
		{
			up_parm = 2.f;
			front_parm = 2.5f;
		}
		bool_TP_to_FP = !bool_TP_to_FP;
	}

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
			shader = ShaderManager::Instance()->GetShader("LightCubeShader");
			shader.Use();
			shader.setMat4("view", c.GetViewMatrix());
			shader.setMat4("projection", c.GetPerspectiveMatrix());
			auto model = glm::mat4(1.0f);
			
			shader.setMat4("model", model);
			glBegin(GL_LINE_STRIP);
			glVertex3f(GetLightPos3().x,GetLightPos3().y,GetLightPos3().z);
			glVertex3f(m_rayDes.x, m_rayDes.y, m_rayDes.z);
			glEnd();
		}


		Timer += DT;
		if (Timer > 0.1f)
		{
			Timer = 0.f;
			m_rayDes = { 0,0,0 };
			is_fire = false;
		}
	}
}



glm::vec3 SpaceShip::GetLightPos1() const
{
	glm::vec3 lightPos(0.0f);
	lightPos.x = -0.5f;
	lightPos.y = 0.8f;
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
	lightPos.y = 0.8f;
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
	lightPos.y = 1.f;
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


void SpaceShip::OnCollision(const string& group, object* other)
{

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
	position -= up * 3.f;
	position += front * 8.0f;
	pos = position;
}
