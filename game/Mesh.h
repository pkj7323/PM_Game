#pragma once


class Shader;
class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();
	void Draw(Shader shader);


	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
private:

	GLuint VAO, VBO, EBO;
	void setupMesh();
};
