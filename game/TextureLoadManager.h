#pragma once
class TextureLoadManager
{
	SINGLE(TextureLoadManager)
private:
	unordered_map<string, GLuint> m_texture;
public:
	void Load(const string& name,const string& filename);

	//return texture id = GLuint
	GLuint Use(const string& name);

	void loadCubeMap(const string& name, vector<string> faces);
	
};

