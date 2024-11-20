#pragma once
struct AABB
{
	float min_x;
	float max_x;
	float min_y;
	float max_y;
	float min_z;
	float max_z;
	void Draw()
	{
		glBegin(GL_LINE_STRIP);
		//bb의 점이용해서 큐브 그리기
		glVertex3f(min_x, min_y, min_z);
		glVertex3f(max_x, min_y, min_z);
		glVertex3f(max_x, max_y, min_z);
		glVertex3f(min_x, max_y, min_z);
		glVertex3f(min_x, min_y, min_z);
		glVertex3f(min_x, min_y, max_z);
		glVertex3f(max_x, min_y, max_z);
		glVertex3f(max_x, min_y, min_z);
		glVertex3f(max_x, min_y, max_z);
		glVertex3f(max_x, max_y, max_z);
		glVertex3f(max_x, max_y, min_z);
		glVertex3f(max_x, max_y, max_z);
		glVertex3f(min_x, max_y, max_z);
		glVertex3f(min_x, max_y, min_z);
		glVertex3f(min_x, max_y, max_z);
		glVertex3f(min_x, min_y, max_z);
		glEnd();
	}
};


class object
{
	glm::vec3 sizeBB;
public:
	object() = default;
	virtual ~object() = default;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual AABB GetBB() = 0;
	virtual void OnCollision(const string& group,object* other) = 0;
	virtual void OnCollisionEnd(const string& group,object* other) = 0;

	void SetSizeBB(const glm::vec3& size) { sizeBB = size; }
	glm::vec3 GetSizeBB() { return sizeBB; }
};

