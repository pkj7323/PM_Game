#pragma once
#include "Mesh.h"
class Shader;
class Model
{
public:
	Model(const string& path, bool gamma = false);
	Model() = default;
	~Model();
	void Draw(Shader shader);
	void ChangeMode(GLuint mode);
private:
	vector<Mesh> meshes;
	vector<Texture> textures_loaded;
	string directory;
	bool gammaCorrection;


	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	static unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
};

