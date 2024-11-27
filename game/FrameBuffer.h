#pragma once
class FrameBuffer
{
	float m_quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};
	GLuint quadVAO, quadVBO;
	GLuint fbo;
	GLuint rbo;
	GLuint textureColorBufferMultiSampled;
	unsigned int intermediateFBO;
	unsigned int screenTexture;
public:
	FrameBuffer();
	~FrameBuffer();
	void Init();
	void Bind();
	void Unbind();
	void Render();
	void Release();
};

