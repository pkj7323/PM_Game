#include "stdafx.h"
#include "SpaceShip.h"

SpaceShip::SpaceShip() : object("space_ship")
{
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
	object::Update();
}

void SpaceShip::Draw(Shader& shader)
{
	object::Draw(shader);
}

void SpaceShip::Move(glm::vec3 position, glm::vec3 up, glm::vec3 front)
{
	position -= up * 2.f;
	position += front * 2.5f;
	pos = glm::vec3(position.x, position.y - 2.f, position.z - 5.f);
}

glm::vec3 SpaceShip::GetLightPos1() const
{
	glm::vec3 lightPos(1.0f);
	lightPos.x -= 1.5f;
	lightPos.y += 0.f;
	lightPos.z += 0.5f;
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
	glm::vec3 lightPos(1.0f);
	lightPos.x -= 0.5f;
	lightPos.y += 0.f;
	lightPos.z += 0.5f;
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
	this->Move(camera.GetPosition(), camera.GetUp(), camera.GetFront());
}


void SpaceShip::OnCollision(const string& group, object* other)
{
}

void SpaceShip::OnCollisionEnd(const string& group, object* other)
{
}
