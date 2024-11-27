#include "stdafx.h"
#include "CollisionManager.h"

#include "object.h"


void CollisionManager::Init()
{
	CollisionMap.clear();
}

void CollisionManager::Update()
{
	std::unordered_map<object*, std::unordered_map<object*, bool>> currentCollisions;

	for (auto& pair : CollisionMap)
	{
		auto& pairs = pair.second;
		auto& left = pairs[0];
		auto& right = pairs[1];
		for (auto& a : left)
		{
			for (auto& b : right)
			{
				bool wasColliding = CollisionCheck(pair.first, a, b);
				bool isColliding = previousCollisions[a][b];

				if (wasColliding)
				{
					a->OnCollision(pair.first, b);
					b->OnCollision(pair.first, a);
					currentCollisions[a][b] = true;
				}
				else if (isColliding)
				{
					a->OnCollisionEnd(pair.first, b);
					b->OnCollisionEnd(pair.first, a);
					currentCollisions[a][b] = false;
				}
			}
		}
	}
	previousCollisions = currentCollisions;
}

void CollisionManager::AddObject(const string& group, object* a, object* b)
{
	if (CollisionMap.find(group) == CollisionMap.end())
	{
		CollisionMap[group] = { {},{} };
	}
	if (a)
		CollisionMap[group][0].push_back(a);
	if (b)
		CollisionMap[group][1].push_back(b);
}

void CollisionManager::RemoveObject(object* obj)
{
	for (auto& pair : CollisionMap)
	{
		auto& pairs = pair.second;
		auto& left = pairs[0];
		auto& right = pairs[1];
		left.erase(std::remove(left.begin(), left.end(), obj), left.end());
		right.erase(std::remove(right.begin(), right.end(), obj), right.end());
	}
}

bool CollisionManager::CollisionCheck(const string& group, object* left, object* right)
{
	
	AABB leftBB = left->GetBB();
	AABB rightBB = right->GetBB();
	if (group == "Robot:Block")
	{
		
	}
	if (leftBB.max_x < rightBB.min_x || leftBB.min_x > rightBB.max_x) return false;
	if (leftBB.max_y < rightBB.min_y || leftBB.min_y > rightBB.max_y) return false;
	if (leftBB.max_z < rightBB.min_z || leftBB.min_z > rightBB.max_z) return false;

	return true;
}

void CollisionManager::Release()
{
	CollisionMap.clear();
	previousCollisions.clear();
}
