#include "stdafx.h"
#include "Rock.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Shader.h"
#include "SoundManager.h"
#include "TimeManager.h"
#include "SpaceShip.h"

Rock::Rock() : object("rock")
{
	CollisionManager::Instance()->AddObject("Mouse:Rock", nullptr, this);
	CollisionManager::Instance()->AddObject("SpaceShip:Rock", nullptr, this);
	m_pos = { randPos(math::dre),randPos(math::dre), -100 };
	speed = randSpeed(math::dre);
	type = Type(randType(math::dre));
	bs.center={ 0, 0.5, 0 };
	if (type == Type::Spin) {
		radius = 14.f;
	}
	bs.radius = 2;
	m_mat_r = glm::mat4(1.0f);
	m_mat_t = glm::mat4(1.0f);
	m_mat_t = glm::translate(m_mat_t, m_pos);
	m_mat_r = glm::rotate(m_mat_r, glm::radians(m_rotate), glm::vec3(0, 0, 1));
	m_mat_r = glm::translate(m_mat_r, glm::vec3(radius, 0, 0));
	pos = glm::vec3(m_mat_r * glm::vec4(0, 0, 0, 1.0f));
	pos = glm::vec3(m_mat_t * glm::vec4(pos, 1.0f));
}

Rock::~Rock()
{
	CollisionManager::Instance()->RemoveObject(this);
}

void Rock::Init()
{
	m_mat_r = glm::mat4(1.0f);
	m_mat_t = glm::mat4(1.0f);
	m_mat_t = glm::translate(m_mat_t, m_pos);
	m_mat_r = glm::rotate(m_mat_r, glm::radians(m_rotate), glm::vec3(0, 0, 1));
	m_mat_r = glm::translate(m_mat_r, glm::vec3(radius, 0, 0));
	pos = glm::vec3(m_mat_r * glm::vec4(0, 0, 0, 1.0f));
	pos = glm::vec3(m_mat_t * glm::vec4(pos, 1.0f));
	object::Init();
}

void Rock::Update()
{
	if (isDead)
	{
		
	}
	else
	{
		switch (type)
		{
		case Type::Normal: {
			speed += 8.f * DT;
			m_pos += speed * DT * direction;
			rotation.x += speed * DT;
			break;
			}
		case Type::Spin:{
			speed += 8.f * DT;
			m_pos += speed * DT * direction;
			rotation.x += speed * DT;
			m_rotate += 3 * speed * DT;
			break;
			}
		default:
			break;
		}
	}

	m_mat_r = glm::mat4(1.0f);
	m_mat_t = glm::mat4(1.0f);
	m_mat_t = glm::translate(m_mat_t, m_pos);
	m_mat_r = glm::rotate(m_mat_r, glm::radians(m_rotate) , glm::vec3(0, 0, 1));
	m_mat_r = glm::translate(m_mat_r, glm::vec3 (radius , 0 , 0));
	pos = glm::vec3(m_mat_r * glm::vec4(0 ,0 ,0, 1.0f));
	pos = glm::vec3(m_mat_t * glm::vec4(pos ,1.0f));
	
	

	if (pos.x > 200 || pos.x < -200 || pos.y > 200 || pos.y < -200 || pos.z > 200 || pos.z < -200)
	{
		naturalDead = true;
	}


	object::Update();
}

void Rock::Draw(Shader& shader)
{
	shader.setFloat("time", timer);
	object::Draw(shader);
}

void Rock::OnCollision(const string& group, object* other)
{
	if (group == "Mouse:Rock" && isDead == false)
	{
		SoundManager::Instance()->Play("explosion_effect");
		SceneManager::Instance()->CurrentSceneDeleteObject<Rock>(this);
		CollisionManager::Instance()->RemoveObject(this);
		isDead = true;
	}
	
}

void Rock::OnCollisionEnd(const string& group, object* other)
{
}

void Rock::SetDirection(const SpaceShip& spaceship)
{
	direction = glm::normalize(spaceship.GetPos() - pos);
}




