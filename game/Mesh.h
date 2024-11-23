#pragma once


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
private:

	GLuint VBO, EBO;
	void setupMesh();
};
