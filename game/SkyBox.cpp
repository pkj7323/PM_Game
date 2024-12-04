#include "stdafx.h"
#include "SkyBox.h"

#include "TextureLoadManager.h"

SkyBox::SkyBox()
{
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

SkyBox::~SkyBox()
{
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteVertexArrays(1, &skyboxVAO);
}

void SkyBox::Draw(Shader& shader)
{
	glDepthFunc(GL_LEQUAL);  
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureLoadManager::Instance()->GetTexture("skybox"));
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDepthFunc(GL_LESS);
}
