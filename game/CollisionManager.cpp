#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
= default;
CollisionManager::~CollisionManager()
{
	Release();
}


void CollisionManager::Init()
{
	CollisionMap.clear();
}
void CollisionManager::Release()
{
	CollisionMap.clear();
	previousCollisions.clear();
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
	
	BoundingSphere leftBB = left->GetBS();
	BoundingSphere rightBB = right->GetBS();
	if (group == "Robot:Block")
	{
		
	}
	
	float distance = glm::distance(leftBB.center, rightBB.center);
	float sumRadius = leftBB.radius + rightBB.radius;
	if (distance < sumRadius)
	{
		return true;
	}


	return false;
}

void CollisionManager::Mouse(int button, int state, int x, int y,const Camera& camera)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);
		//마우스 클릭 위치를 NDC로 변환
		float x_ndc = (2.0f * static_cast<float>(x)) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
		float y_ndc = 1.0f - (2.0f * static_cast<float>(y)) / glutGet(GLUT_WINDOW_HEIGHT);
		float z_ndc = 1.0f;
		glm::vec3 ray_position = camera.GetPosition();
		glm::vec3 ray_direction = RayCalculate({ x_ndc,y_ndc,z_ndc }, camera);
		for (auto& [fst, snd] : CollisionMap)
		{
			auto& pairs = snd;
			auto& left = pairs[0];
			auto& right = pairs[1];
			for (auto& a : left)//아마 안불릴듯 마우스 객체는 없기 때문에
			{
				
				/*if (!IsInViewFrustum(a->GetBS().center, camera))
				{
					return;
				}*/
				if (RayIntersectsSphere(ray_position, ray_direction, a->GetBS(), camera))
				{
					a->OnCollision(fst, nullptr);
				}
			}
			for (auto& b : right)
			{
				/*if (!IsInViewFrustum(b->GetBS().center, camera))
				{
					return;
				}*/
				if (RayIntersectsSphere(ray_position, ray_direction, b->GetBS(), camera))
				{
					b->OnCollision(fst, nullptr);
				}
			}

		}
	}
}
bool CollisionManager::RayIntersectsSphere(const glm::vec3& ray_pos, const glm::vec3& ray_dir,
	const BoundingSphere& bs, const Camera& camera)
{
	glm::vec3 d = ray_dir;
	glm::vec3 s = ray_pos;
	glm::vec3 c = bs.center;
	double A = d.x * d.x + d.y * d.y + d.z * d.z;
	double B = 2 * (d.x * (s.x - c.x) + d.y * (s.y - c.y) + d.z * (s.z - c.z));
	double C = (s.x - c.x) * (s.x - c.x) + (s.y - c.y) * (s.y - c.y) + (s.z - c.z) * (s.z - c.z) - bs.radius * bs.radius;

	double judge = B * B - 4 * A * C;
	
	if (judge >= 0)
	{
		//만난점의 위치 = t
		float t1 = (-B + sqrt(judge)) / (2 * A);
		float t2 = (-B - sqrt(judge)) / (2 * A);
		float t = 0;
		if (t1 >= t2)
			t = t2;
		else
			t = t1;
		if (t < camera.GetNear())//전방평면 앞에 있으면
		{
			return false;
		}
		if (t > camera.GetFar())//후방평면 뒤에 있으면
		{
			return false;
		}
		return true;
	}

	return false;
}
glm::vec3 CollisionManager::RayCalculate(const glm::vec3& ndc_pos, const Camera& camera)
{
	// NDC를 클립 좌표로 변환
	glm::vec4 rayClip = glm::vec4(ndc_pos.x, ndc_pos.y, -1.0f, 1.0f);

	// 클립 좌표를 뷰 좌표로 변환
	glm::vec4 rayEye = glm::inverse(camera.GetPerspectiveMatrix()) * rayClip;
	rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);

	// 뷰 좌표를 월드 좌표로 변환
	glm::vec3 rayWorld = glm::vec3(glm::inverse(camera.GetViewMatrix()) * rayEye);
	rayWorld = glm::normalize(rayWorld);

	return rayWorld;//카메라에서 나가는 광선의 방향
}
bool CollisionManager::IsInViewFrustum(const glm::vec3& pos, const Camera& camera)
{
	// 카메라의 뷰 프러스텀 내에 있는지 확인
	glm::vec4 clipPos = camera.GetPerspectiveMatrix() * camera.GetViewMatrix() * glm::vec4(pos, 1.0f);
	clipPos /= clipPos.w;
	if (clipPos.x < -1.0f || clipPos.x > 1.0f || clipPos.y < -1.0f || clipPos.y > 1.0f || clipPos.z < -1.0f || clipPos.z > 1.0f)
	{
		return false;
	}

	return true;
}
bool CollisionManager::RayIntersectsBS(const glm::vec3& ray_origin, const glm::vec3& ray_dir, const BoundingSphere& bs, const Camera& camera)
{
	// 카메라의 뷰 프러스텀 내에 있는지 확인
	if (!IsInViewFrustum(bs.center, camera)) {
		return false; // 뷰 프러스텀 밖에 있는 경우
	}
	glm::vec3 L = bs.center - ray_origin;
	double s = glm::dot(L, ray_dir);
	double l2 = glm::dot(L, L);
	double r2 = bs.radius * bs.radius;

	if (s < 0 && l2 > r2)
	{
		return false; // 광선의 시작점이 구의 뒤쪽에 있고 구와 광선이 만나지 않는 경우
	}

	double m2 = l2 - s * s;

	if (m2 > r2)
	{
		return false; // 광선과 구가 만나지 않는 경우
	}

	double q = sqrt(r2 - m2);
	double t0 = s - q;
	double t1 = s + q;

	if (t0 < 0 && t1 < 0)
	{
		return false; // 광선이 구를 통과하지 않는 경우
	}
	//double q = sqrt(r2 - m2);
	// 전방 평면과 후방 평면을 넘어가는 경우 체크
	/*if (l2 > r2)
	{
		auto distance = s - q;
	}
	else
	{
		auto distance = s + q;
	}*/

	return true;
	
}



// 레이와 AABB 충돌 검사 함수
bool CollisionManager::RayIntersectsAABB(const glm::vec3& ray, const AABB& aabb) {
	float tmin = (aabb.min_x - ray.x) / ray.x;
	float tmax = (aabb.max_x - ray.x) / ray.x;

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (aabb.min_y - ray.y) / ray.y;
	float tymax = (aabb.max_y - ray.y) / ray.y;

	if (tymin > tymax) std::swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (aabb.min_z - ray.z) / ray.z;
	float tzmax = (aabb.max_z - ray.z) / ray.z;

	if (tzmin > tzmax) std::swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	return true;
}


