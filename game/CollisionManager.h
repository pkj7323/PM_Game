#pragma once
#include "Camera.h"
#include "object.h"
class CollisionManager
{
	SINGLE(CollisionManager)
public:
	void Init();
	void Update();
	void AddObject(const string& group, object* a, object* b);
	void RemoveObject(object* obj);
	bool CollisionCheck(const string& group, object* left, object* right);
	void Mouse(int button, int state, int x, int y, const Camera& camera, glm::vec3& collision_point);
	glm::vec3 RayCalculate(const glm::vec3& ray, const Camera& camera);
	bool IsInViewFrustum(const glm::vec3& pos, const Camera& camera);

	bool RayIntersectsAABB(const glm::vec3& ray, const AABB& aabb);
	bool RayIntersectsBS(const glm::vec3& ray_origin, const glm::vec3& ray_dir, const BoundingSphere& bs, const Camera& camera);
	bool RayIntersectsSphere(const glm::vec3& ray_pos, const glm::vec3& ray_dir, const BoundingSphere& bs, const Camera& camera
	,glm::vec3& collision_point);
	void Release();

	glm::vec3 GetRayDes() { return m_rayDes; }
private:
	std::unordered_map<object*, std::unordered_map<object*, bool>> previousCollisions;
	unordered_map<string, vector<vector<object*>>> CollisionMap;
	glm::vec3 m_rayDes{};
};

