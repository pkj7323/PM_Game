#include "stdafx.h"
#include "object.h"
#include "ModelManager.h"
#include "Shader.h"


object::object(const string& name) : pos(0), scale(1), rotation(0), Matrix(1)
, parentMatrix(1), timer(0), isDead(false)

{
	model = ModelManager::Instance()->GetModel(name);
}

void object::Init()
{
	Matrix = glm::mat4(1.0f);
	Matrix = glm::translate(Matrix, pos);
	Matrix = glm::scale(Matrix, scale);
	Matrix = glm::rotate(Matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	Matrix = glm::rotate(Matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	Matrix = glm::rotate(Matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
}

void object::Init(const string& name)
{
	model = ModelManager::Instance()->GetModel(name);
	parentMatrix = glm::mat4(1.0f);
	Matrix = glm::mat4(1.0f);
	Matrix = glm::translate(Matrix, pos);
	Matrix = glm::scale(Matrix, scale);
	Matrix = glm::rotate(Matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	Matrix = glm::rotate(Matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	Matrix = glm::rotate(Matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	Matrix = parentMatrix * Matrix;
}

void object::Update()
{
	Matrix = glm::mat4(1.0f);
	Matrix = glm::translate(Matrix, pos);
	Matrix = glm::scale(Matrix, scale);
	Matrix = glm::rotate(Matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	Matrix = glm::rotate(Matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	Matrix = glm::rotate(Matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

	Matrix = parentMatrix * Matrix;
}

void object::Draw(Shader& shader)
{
	shader.setMat4("model", Matrix);
	model.Draw(shader);
	bs.Draw();
}
