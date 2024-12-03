#include "stdafx.h"
#include "Earth.h"

#include "Shader.h"

Earth::Earth() : object("sphere")
{

}

Earth::~Earth()
{
}

void Earth::Init()
{
	object::Init();
}

void Earth::Update()
{
	object::Update();
}

void Earth::Draw(Shader& shader)
{
	shader.Use();
	object::Draw(shader);
}

void Earth::OnCollision(const string& group, object* other)
{
}

void Earth::OnCollisionEnd(const string& group, object* other)
{
}
