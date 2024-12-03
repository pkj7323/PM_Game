#include "stdafx.h"
#include "Pyramid.h"
#include "Mesh.h"
#include "TextureLoadManager.h"

Pyramid::Pyramid() : object("pyramid")
{
}

Pyramid::~Pyramid()
{
}

void Pyramid::Init()
{
	object::Init();
}

void Pyramid::Update()
{
    
	object::Update();
}

void Pyramid::Draw(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("cyan"));
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureLoadManager::Instance()->GetTexture("snow_normal_map"));
	object::Draw(shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Pyramid::OnCollision(const string& group, object* other)
{
}

void Pyramid::OnCollisionEnd(const string& group, object* other)
{
}

void Pyramid::Sierpinsky()
{
    vector<Vertex> newVertices;
    vector<unsigned int> newIndices;

    for (size_t i = 0; i < count; i++)
    {
        for (const auto& mesh : model.meshes)
        {
            for (size_t j = 0; j + 2 < mesh.vertices.size(); j += 3)
            {
                // Original triangle vertices
                Vertex v0 = mesh.vertices[j];
                Vertex v1 = mesh.vertices[j + 1];
                Vertex v2 = mesh.vertices[j + 2];

                // Midpoints of the edges
                glm::vec3 m01 = glm::mix(v0.Position, v1.Position, 0.5f);
                glm::vec3 m12 = glm::mix(v1.Position, v2.Position, 0.5f);
                glm::vec3 m20 = glm::mix(v2.Position, v0.Position, 0.5f);

                // Add the vertices of the 3 new triangles
                newVertices.emplace_back(v0);
                Vertex temp = { m01, v0.Normal, v0.TexCoords, v0.Tangent, v0.Bitangent };
                newVertices.emplace_back(temp);
                temp = { m20, v0.Normal, v0.TexCoords, v0.Tangent, v0.Bitangent };
                newVertices.emplace_back(temp);

                temp = { m01, v1.Normal, v1.TexCoords, v1.Tangent, v1.Bitangent };
                newVertices.emplace_back(temp);
                newVertices.emplace_back(v1);
                temp = { m12, v1.Normal, v1.TexCoords, v1.Tangent, v1.Bitangent };
                newVertices.emplace_back(temp);

                temp = { m20, v2.Normal, v2.TexCoords, v2.Tangent, v2.Bitangent };
                newVertices.emplace_back(temp);
                temp = { m12, v2.Normal, v2.TexCoords, v2.Tangent, v2.Bitangent };
                newVertices.emplace_back(temp);
                newVertices.emplace_back(v2);

                // Add the indices of the 3 new triangles
                unsigned int baseIndex = static_cast<unsigned int>(newVertices.size()) - 9;
                newIndices.push_back(baseIndex);
                newIndices.push_back(baseIndex + 1);
                newIndices.push_back(baseIndex + 2);

                newIndices.push_back(baseIndex + 3);
                newIndices.push_back(baseIndex + 4);
                newIndices.push_back(baseIndex + 5);

                newIndices.push_back(baseIndex + 6);
                newIndices.push_back(baseIndex + 7);
                newIndices.push_back(baseIndex + 8);
            }
        }
    }

    // Update the mesh with the new vertices and indices
    model.meshes[0].vertices = newVertices;
    model.meshes[0].indices = newIndices;
    model.meshes[0].updateMesh();
}
