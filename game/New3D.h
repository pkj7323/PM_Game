#pragma once

class New3D
{
protected:
	void InitBuffer();//처음 버퍼 생성, Matrix 업데이트 호출

	
public:
	New3D();
	New3D(const string& path);
	virtual ~New3D();
	void UpdateBuffer();//뭔가 위치를 바꾸려면 matrix 바꿔서 호출 이 함수는 아마 호출할 일 없을것

	virtual void update();//월드행렬 계산
	virtual void draw();//uniform 변수 설정, 그리기

	void SetParentTransform(glm::mat4 matrix) { this->parentTransform = matrix; }
	glm::mat4& GetParentTransform() { return this->parentTransform; }

	
	void RotateSelf(float theta, glm::vec3 basis);
	void Rotate(float degree, glm::vec3 basis);
	void Translate(glm::vec3 scalar);
	void Scale(glm::vec3 scale);
	void ScaleSelf(glm::vec3 scale);

	glm::vec3 CalculateCenter();
	void Move(glm::vec3 target, float scalar);
	void Move(float x,float y, float z, float scalar);

	void TopRotate(float degree,glm::vec3 basis);

	float top_y = INFINITE;


	

	//seter, geter
	GLuint GetVAO() { return VAO; }

	void SetWorldTrans(glm::mat4 worldTrans) { this->worldTransform = worldTrans; }
	glm::mat4 GetWorldTrans() { return worldTransform; }

	void SetModel(Model* model) { this->model = model; }
	Model* GetModel() { return this->model; }



	void SetScale(glm::vec3 scale) { this->scale_factor = scale; }
	glm::vec3& GetScale() { return this->scale_factor; }

	void SetTranslate(glm::vec3 translate) { this->translate_factor = translate; }
	glm::vec3& GetTranslate() { return this->translate_factor; }

	void SetRotate(glm::vec3 rotate) { this->rotate_factor = rotate; }
	glm::vec3& GetRotate() { return this->rotate_factor; }

	//GL_TRIANGLES, GL_LINE_STRIP, GL_LINE_LOOP 등
	void SetMode(unsigned int mode) { this->mode = mode; }
	unsigned int GetMode() const { return this->mode; }

	GLint GetUniformWorld() const { return uniformWorld; }


private:
	GLuint VAO;
	GLuint VBO_pos;
	GLuint VBO_color;
	GLuint VBO_texure;
	GLuint EBO;



	Model* model;

	unsigned int mode;

	glm::mat4 worldTransform;
	glm::mat4 parentTransform;
	glm::vec3 scale_factor;
	glm::vec3 translate_factor;
	glm::vec3 rotate_factor;
};

