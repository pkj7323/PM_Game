#pragma once
#include "Camera.h"
#include "Model.h"

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
		//bb�� ���̿��ؼ� ť�� �׸���
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
struct BoundingSphere
{
	BoundingSphere() : radius(1.0f), center(0.0f) {}
	BoundingSphere(float r, glm::vec3 c) : radius(r), center(c) {}
	float radius;
	glm::vec3 center;
	void Draw()
	{
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; i++)
		{
			float x = center.x + radius * cos(glm::radians(static_cast<float>(i)));
			float y = center.y + radius * sin(glm::radians(static_cast<float>(i)));
			glVertex3f(x, y, center.z);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 360; i++)
		{
			float x = center.x + radius * cos(glm::radians(static_cast<float>(i)));
			float z = center.z + radius * sin(glm::radians(static_cast<float>(i)));
			glVertex3f(x, center.y, z);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (int i=0;i<360; i++)
		{
			float y = center.y + radius * cos(glm::radians(static_cast<float>(i)));
			float z = center.z + radius * sin(glm::radians(static_cast<float>(i)));
			glVertex3f(center.x, y, z);
		}
		glEnd();
	}
};
#define DeathTime 1.0f
class Shader;
class object
{
	
protected:
	Model model;
	glm::vec3 pos;//x,y,z�� ��ġ�� �����ϰ� ���� ��ŭ ���� �� ����
	glm::vec3 scale;//x,y,z�� ũ�⸦ �����ϰ� ���� ��ŭ ���� �� ����
	glm::vec3 rotation;//x,y,z�� ȸ�� �ϰ� ���� ��ŭ ���� �� ���� degree
	glm::mat4 Matrix; // ��� ������ ����� �ƴϰ� ����� �ָ� �޾� ���� �� �ֵ���
	glm::mat4 parentMatrix; // �θ��� Matrix
	BoundingSphere bs;//�浹üũ�� ���� bounding sphere

	float time_to_die = DeathTime;
	float timer;
	bool isDead;
public:
	object(const string& name);
	virtual ~object() = default;

	virtual void Init();
	virtual void Init(const string& name);
	virtual void Update();
	virtual void Draw(Shader& shader);

	//void SetMatrix(const glm::mat4& mat) { Matrix = mat; }
	glm::mat4 GetMatrix() const { return Matrix; }


	BoundingSphere GetBS()
	{
		auto center = glm::translate(glm::mat4(1.0f), pos) * glm::vec4(bs.center, 1.0f);
		return {bs.radius,center};
	}
	virtual void OnCollision(const string& group,object* other) = 0;
	virtual void OnCollisionEnd(const string& group,object* other) = 0;
};

