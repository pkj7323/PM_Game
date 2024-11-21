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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩 
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->faces.size() * sizeof(glm::uvec3), model->faces.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//각 정점의 데이터 (타입)를 저장
   //void glVertexAttribPointer(
   //	GLuint index,        // 속성 인덱스
   //	GLint size,          // 요소의 개수 (예: 3이면 x, y, z)
   //	GLenum type,         // 각 요소의? 데이터 타입 (예: GL_FLOAT)
   //	GLboolean normalized,// 정규화 여부 (GL_TRUE 또는 GL_FALSE)
   //	GLsizei stride,      // 다음 요소까지의 바이트 간격
   //	const void* pointer  // 버퍼 데이터의 시작 위치
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩 
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
	//월드 행렬 부르기



	assert(VAO != NULL && "VAO 설정안됨");

	assert(VBO_pos != NULL && "VBO_pos 설정안됨");
	assert(VBO_color != NULL && "VBO_color 설정안됨");
	assert(VBO_texure != NULL && "VBO_texure 설정안됨");
	assert(EBO != NULL && "EBO 설정안됨");




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
	// 중심을 원점으로 이동합니다.
	glm::mat4 translateToOrigin = glm::translate(glm::mat4(1.0f), -center);

	// 중심을 원점으로 이동한 후 회전 변환을 적용합니다.
	glm::mat4 rotateTransform = glm::rotate(glm::mat4(1.0f), glm::radians(degree), basis);

	// 원점에서 다시 중심으로 이동합니다.
	glm::mat4 translateBack = glm::translate(glm::mat4(1.0f), center);

	// 변환 행렬을 결합합니다.
	glm::mat4 transform = translateBack * rotateTransform * translateToOrigin;

	// 변환을 적용합니다.
	for (auto& vertex : model->vertices)
	{
		vertex = glm::vec3(transform * glm::vec4(vertex, 1.0f));
	}
	UpdateBuffer();
	// 회전 변환을 업데이트합니다.
	

	
	
}

//glGenTextures(1, &texture);// 텍스처 객체 생성
//glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
//glBindTexture(GL_TEXTURE_2D, texture);
///*float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };//경계모드 바깥쪽 색깔 설정
//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/
////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);// 확대 축소시 샘플링 방법 설정
////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);// 축소 확대시 샘플링 방법 설정
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//int width, height, nrChannels;
//unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
//if (data)
//{
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//	/*첫 번째 인수는 텍스처 대상을 지정합니다.
//	이를 GL_TEXTURE_2D 로 설정하면 이 작업은 동일한 대상에서 현재 바인딩된 텍스처 객체에 텍스처를 생성합니다
//	(따라서 GL_TEXTURE_1D 또는 GL_TEXTURE_3D 대상에 바인딩된 모든 텍스처는 영향을 받지 않습니다).
//
//	두 번째 인수는 수동으로 각 밉맵 레벨을 설정하려는 경우 텍스처를 생성할 밉맵 레벨을 지정하지만,
//	우리는 기본 레벨인 0으로 둡니다.
//
//	세 번째 인수는 OpenGL에 텍스처를 어떤 형식으로 저장할지 알려줍니다.
//	이미지에는 RGB값만 있으므로 텍스처도 RGB값과 함께 저장합니다.
//
//	네 번째와 다섯 번째 인수는 텍스처의 너비와 높이입니다.
//	이미지를 로드할 때 이전에 저장했으므로 해당 변수를 사용합니다.
//
//	다음 인수(6번째)는 항상 0(일부 레거시 항목)이어야 합니다.
//
//	7번째와 8번째 인수는 소스 이미지의 형식과 데이터 유형을 지정합니다.
//	우리는 이미지에 RGB값을 로드하고 s(바이트)로 저장했으므로 char해당 값을 전달합니다.
//
//	마지막 인수는 실제 이미지 데이터입니다*/
//	glGenerateMipmap(GL_TEXTURE_2D);// 미리 계산된 mipmap 생성
//}
//else
//{
//	std::cout << "Failed to load texture" << std::endl;
//}
//stbi_image_free(data);// 이미지 데이터 삭제