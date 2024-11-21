#include "stdafx.h"
#include "New3D.h"
#include "ShaderManager.h"



New3D::New3D() : VAO{ NULL }, VBO_pos{ NULL }, VBO_color{ NULL }
                 , VBO_texure{ NULL }, EBO{ NULL }, model{ nullptr }
                 , mode{ GL_TRIANGLES }
{
	model = new Model("NULL");
	worldTransform = glm::mat4(1.0f);
	parentTransform = glm::mat4(1.0f);
	scale_factor = glm::vec3(1, 1, 1);
	translate_factor = glm::vec3(0, 0, 0);
	rotate_factor = glm::vec3(0, 0, 0);

	
	

	InitBuffer();
}

New3D::New3D(const string& path) : VAO{ NULL }, VBO_pos{ NULL }, VBO_color{ NULL }
, VBO_texure{ NULL }, EBO{ NULL }, model{ nullptr }
, mode{ GL_TRIANGLES }
{
	

	model = new Model(path);
	worldTransform = glm::mat4(1.0f);
	parentTransform = glm::mat4(1.0f);
	scale_factor = glm::vec3(1, 1, 1);
	translate_factor = glm::vec3(0, 0, 0);
	rotate_factor = glm::vec3(0, 0, 0);


	


	InitBuffer();
}

void New3D::InitBuffer()
{
	update();
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO_pos);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
	glBufferData(GL_ARRAY_BUFFER, model->vertices.size() * sizeof(glm::vec3), model->vertices.data(), GL_STATIC_DRAW);


	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //--- GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε� 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->faces.size() * sizeof(glm::uvec3), model->faces.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//�� ������ ������ (Ÿ��)�� ����
   //void glVertexAttribPointer(
   //	GLuint index,        // �Ӽ� �ε���
   //	GLint size,          // ����� ���� (��: 3�̸� x, y, z)
   //	GLenum type,         // �� �����? ������ Ÿ�� (��: GL_FLOAT)
   //	GLboolean normalized,// ����ȭ ���� (GL_TRUE �Ǵ� GL_FALSE)
   //	GLsizei stride,      // ���� ��ұ����� ����Ʈ ����
   //	const void* pointer  // ���� �������� ���� ��ġ
   //);

	glGenBuffers(1, &VBO_color);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, model->colors.size() * sizeof(glm::vec3), model->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &VBO_texure);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_texure);
	glBufferData(GL_ARRAY_BUFFER, model->texture_coords.size() * sizeof(glm::vec3), model->texture_coords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}


New3D::~New3D()
{
	delete model;
	glDeleteBuffers(1, &VBO_pos);
	glDeleteBuffers(1, &VBO_color);
	glDeleteBuffers(1, &VBO_texure);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);

}

void New3D::UpdateBuffer()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
	glBufferData(GL_ARRAY_BUFFER, model->vertices.size() * sizeof(glm::vec3), model->vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //--- GL_ELEMENT_ARRAY_BUFFER ���� �������� ���ε� 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->faces.size() * sizeof(glm::uvec3), model->faces.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
	glBufferData(GL_ARRAY_BUFFER, model->colors.size() * sizeof(glm::vec3), model->colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_texure);
	glBufferData(GL_ARRAY_BUFFER, GetModel()->texture_coords.size() * sizeof(glm::vec3), GetModel()->texture_coords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}

void New3D::update()
{
	glm::mat4 scaleTransform = glm::scale(glm::mat4(1.0f), scale_factor);
	glm::mat4 translateTransform = glm::translate(glm::mat4(1.0f), translate_factor);
	glm::mat4 rotateTransform = glm::rotate(glm::mat4(1.0f), rotate_factor.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotateTransform = glm::rotate(rotateTransform, rotate_factor.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotateTransform = glm::rotate(rotateTransform, rotate_factor.z, glm::vec3(0.0f, 0.0f, 1.0f));
	worldTransform = translateTransform * rotateTransform * scaleTransform;
	worldTransform = parentTransform * worldTransform;
}

void New3D::draw()
{
	//GLuint shaderProgram = ShaderManager::Instance()->GetID();
	//���� ��� �θ���



	assert(VAO != NULL && "VAO �����ȵ�");

	assert(VBO_pos != NULL && "VBO_pos �����ȵ�");
	assert(VBO_color != NULL && "VBO_color �����ȵ�");
	assert(VBO_texure != NULL && "VBO_texure �����ȵ�");
	assert(EBO != NULL && "EBO �����ȵ�");




	glBindVertexArray(VAO);
	glDrawElements(mode, 3 * model->faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void New3D::RotateSelf(float degree, glm::vec3 basis)
{
	basis = glm::normalize(basis);
	rotate_factor.x += glm::radians(degree) * basis.x;
	rotate_factor.y += glm::radians(degree) * basis.y;
	rotate_factor.z += glm::radians(degree) * basis.z;
	New3D::update();
}

void New3D::Rotate(float degree, glm::vec3 basis)
{
	translate_factor = glm::rotate(glm::mat4(1.0f), glm::radians(degree), basis) * glm::vec4(translate_factor, 1.0f);
	New3D::update();
}

void New3D::Translate(glm::vec3 scalar)
{
	translate_factor.x += scalar.x;
	translate_factor.y += scalar.y;
	translate_factor.z += scalar.z;
	New3D::update();
}

void New3D::Scale(glm::vec3 scale)
{
	translate_factor *= scale;
	scale_factor *= scale;
	New3D::update();
}

void New3D::ScaleSelf(glm::vec3 scale)
{
	scale_factor *= scale;
	New3D::update();
}

glm::vec3 New3D::CalculateCenter()
{
	glm::vec3 center(0, 0, 0);
	for (auto& vertex : model->vertices)
	{
		center += vertex;
	}
	center /= model->vertices.size();
	
	return center;
}

void New3D::Move(glm::vec3 target, float scalar)
{
	
	
	auto dis = glm::distance(target, translate_factor);
	if (dis == 0) {
		return;
	}
	auto dir = glm::normalize(target - translate_factor) * scalar;

	translate_factor = glm::translate(glm::mat4(1.0f), dir) * glm::vec4(translate_factor, 1.0f);
	New3D::update();
}

void New3D::Move(float x, float y, float z, float scalar)
{
	Move(glm::vec3(x, y, z), scalar);
}

void New3D::TopRotate(float degree, glm::vec3 basis)
{
	glm::vec3 center = CalculateCenter();
	if (top_y == INFINITE)
	{
		top_y = model->vertices.back().y;
	}
	center.y += top_y - center.y;
	// �߽��� �������� �̵��մϴ�.
	glm::mat4 translateToOrigin = glm::translate(glm::mat4(1.0f), -center);

	// �߽��� �������� �̵��� �� ȸ�� ��ȯ�� �����մϴ�.
	glm::mat4 rotateTransform = glm::rotate(glm::mat4(1.0f), glm::radians(degree), basis);

	// �������� �ٽ� �߽����� �̵��մϴ�.
	glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), center);

	// ��ȯ ����� �����մϴ�.
	glm::mat4 transform = translateBack * rotateTransform * translateToOrigin;

	// ��ȯ�� �����մϴ�.
	for (auto& vertex : model->vertices)
	{
		vertex = glm::vec3(transform * glm::vec4(vertex, 1.0f));
	}
	UpdateBuffer();
	// ȸ�� ��ȯ�� ������Ʈ�մϴ�.
	

	
	
}

//glGenTextures(1, &texture);// �ؽ�ó ��ü ����
//glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
//glBindTexture(GL_TEXTURE_2D, texture);
///*float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };//����� �ٱ��� ���� ����
//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/
////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// Ȯ�� ��ҽ� ���ø� ��� ����
////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// ��� Ȯ��� ���ø� ��� ����
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//int width, height, nrChannels;
//unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
//if (data)
//{
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	/*ù ��° �μ��� �ؽ�ó ����� �����մϴ�.
//	�̸� GL_TEXTURE_2D �� �����ϸ� �� �۾��� ������ ��󿡼� ���� ���ε��� �ؽ�ó ��ü�� �ؽ�ó�� �����մϴ�
//	(���� GL_TEXTURE_1D �Ǵ� GL_TEXTURE_3D ��� ���ε��� ��� �ؽ�ó�� ������ ���� �ʽ��ϴ�).
//
//	�� ��° �μ��� �������� �� �Ӹ� ������ �����Ϸ��� ��� �ؽ�ó�� ������ �Ӹ� ������ ����������,
//	�츮�� �⺻ ������ 0���� �Ӵϴ�.
//
//	�� ��° �μ��� OpenGL�� �ؽ�ó�� � �������� �������� �˷��ݴϴ�.
//	�̹������� RGB���� �����Ƿ� �ؽ�ó�� RGB���� �Բ� �����մϴ�.
//
//	�� ��°�� �ټ� ��° �μ��� �ؽ�ó�� �ʺ�� �����Դϴ�.
//	�̹����� �ε��� �� ������ ���������Ƿ� �ش� ������ ����մϴ�.
//
//	���� �μ�(6��°)�� �׻� 0(�Ϻ� ���Ž� �׸�)�̾�� �մϴ�.
//
//	7��°�� 8��° �μ��� �ҽ� �̹����� ���İ� ������ ������ �����մϴ�.
//	�츮�� �̹����� RGB���� �ε��ϰ� s(����Ʈ)�� ���������Ƿ� char�ش� ���� �����մϴ�.
//
//	������ �μ��� ���� �̹��� �������Դϴ�*/
//	glGenerateMipmap(GL_TEXTURE_2D);// �̸� ���� mipmap ����
//}
//else
//{
//	std::cout << "Failed to load texture" << std::endl;
//}
//stbi_image_free(data);// �̹��� ������ ����