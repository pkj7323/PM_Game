#include "stdafx.h"
#include "Mars.h"

#include "TextureLoadManager.h"
#include "TimeManager.h"

Mars::Mars() : object("sphere")
{
	pos = { 200 + 100,0,-40 };
	scale = { 2,2,2 };
}

Mars::~Mars()
{
}

void Mars::Init()
{
	object::Init();
}

void Mars::Init(const string& name)
{
	
	object::Init(name);
}

void Mars::Update()
{
	pos = glm::rotate(glm::mat4(1.0f), glm::radians(0.53f * DT), glm::vec3(0, 1, 0)) * glm::vec4(pos, 1.0f);
	parentMatrix = glm::translate(glm::mat4(1.0f), { -200,0,-40 });
	object::Update();
}

void Mars::Draw(Shader& shader)
{
	TextureLoadManager::Instance()->Use("mars");
	TextureLoadManager::Instance()->Use("mars_normal_map",2);
	object::Draw(shader);
	TextureLoadManager::Instance()->Unbind(2);
}

void Mars::OnCollision(const string& group, object* other)
{
}

void Mars::OnCollisionEnd(const string& group, object* other)
{
}
