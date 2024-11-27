#include "stdafx.h"
#include "Rock.h"

Rock::Rock()
{
}

Rock::~Rock()
{
}

void Rock::Init()
{
	SetSizeBB(glm::vec3(5, 5, 5));
}

void Rock::Update()
{
}

void Rock::Draw(Shader& shader)
{
	m_Rock.Draw(shader);
}


void Rock::OnCollision(const string& group, object* other)
{
}

void Rock::OnCollisionEnd(const string& group, object* other)
{
}

AABB Rock::GetBB()
{
	return AABB();
}
