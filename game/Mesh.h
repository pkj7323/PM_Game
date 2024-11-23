#pragma once
#define MAX_BONE_INFLUENCE 4
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	float m_Weights[MAX_BONE_INFLUENCE];
};
struct Texture
{
	GLuint id;
	string type;
	string path;
};


class Shader;
class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader& shader);

	GLuint VAO;
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	GLuint mode = GL_TRIANGLES;
private:

	GLuint VBO, EBO;
	void setupMesh();
};
