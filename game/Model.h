#pragma once
#include "Mesh.h"

class Shader;
class Model
{
public:
	Model(const string& path, bool gamma = false);
	Model() = default;
	~Model();
	void Draw(Shader& shader);
	void ChangeMode(GLuint mode);
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	bool gammaCorrection;


	void Move(glm::vec3 position, glm::vec3 up , glm::vec3 front);
	void Rotate_y(float pitch);
	void Rotate_x(float yat);

	glm::vec3 GetPosition() const { return Position; }
	float GetRotate_y() const { return rotate_y; }
	float GetRotate_x() const { return rotate_x; }

private:
	float rotate_y;
	float rotate_x; 
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	static unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
};

