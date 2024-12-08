#include "stdafx.h"
#include "spaceship.h"
#include "TextureLoadManager.h"
#include "KeyManager.h"


Spaceship::Spaceship() : object("space_ship")
{

}

Spaceship::~Spaceship()
{

}

void Spaceship::Init()
{
	object::Init();
}

void Spaceship::Update(){

	if (KEY_HOLD(KEY::A)) {
		if (rotation.z < 45) {
			rotation.z += 0.5f;;
		}
		
	}
	else {
		if (rotation.z >= 0) {
			rotation.z -= 0.5f;
		}
	}
	if (KEY_HOLD(KEY::D)) {
		if (rotation.z > -45) {
			rotation.z -= 0.5f;;
		}
	}
	else {
		if (rotation.z <= 0) {
			rotation.z += 0.5f;;
		}
	}

	object::Update();
}

void Spaceship::Draw(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("space_ship"));
	object::Draw(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Spaceship::OnCollision(const string& group, object* other)
{

}

void Spaceship::OnCollisionEnd(const string& group, object* other)
{

}

void Spaceship::Move(glm::vec3 position, glm::vec3 up, glm::vec3 front)
{
	position -= up * 2.f;
	position += front * 2.5f;
	pos = glm::vec3(position.x, position.y - 2.f, position.z - 5.f);
}

void Spaceship::Rotate_y(float yat)
{
	rotation.y = -(yat+90);
}

void Spaceship::Rotate_x(float pitch)
{
	rotation.x = pitch;
}

