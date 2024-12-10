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
		if (rotation.z >= 0) {
			rotation.z -= 0.5f;
		}
	}
	if (KEY_HOLD(KEY::D)) {
		if (rotation.z > -45) {
			rotation.z -= 0.5f;
		}
	}
	else {
		if (rotation.z <= 0) {
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
		shader = ShaderManager::Instance()->GetShader("PlanetShader");
		shader.Use();
		shader.setMat4("view", c.GetViewMatrix());
		shader.setMat4("projection", c.GetPerspectiveMatrix());
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, GetLightPos3());
		model = glm::scale(model, glm::vec3(0.5f));
		shader.setMat4("model", model);
		TextureLoadManager::Instance()->Unbind(2);
		TextureLoadManager::Instance()->Use("laser_effect");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		laser_effect.Draw(shader);
		glDisable(GL_BLEND);
		TextureLoadManager::Instance()->Unbind(0);
		if (m_rayDes != glm::vec3{0,0,0})
		{
			shader = ShaderManager::Instance()->GetShader("LightCubeShader");
			shader.Use();
			shader.setMat4("view", c.GetViewMatrix());
			shader.setMat4("projection", c.GetPerspectiveMatrix());
			model = glm::mat4(1.0f);
			
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
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	r = glm::rotate(r, glm::radians(rotation.y), glm::vec3(0, 1, 0));
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
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	r = glm::rotate(r, glm::radians(rotation.y), glm::vec3(0, 1, 0));
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
	glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	r = glm::rotate(r, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	r = glm::rotate(r, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	lightPos = glm::vec3(r * glm::vec4(lightPos, 1.0f));
	lightPos = glm::vec3(t * glm::vec4(lightPos, 1.0f));



	return lightPos;
}

void SpaceShip::ProcessMouseMovement(const Camera& camera)
{
	rotation.x = camera.GetPitch();
	rotation.y = -(camera.GetYaw() + 90.f);
	
	this->Move(camera);
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
	position -= up * 3.0f;
	position += front * 6.0f;
	pos = glm::vec3(position.x, position.y, position.z);
}
