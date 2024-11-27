#pragma once
class TextureLoadManager
{
	SINGLE(TextureLoadManager)
private:
	unordered_map<string, GLuint> m_texture;
	
public:
	void Init();
	void Load(const string& name,const string& filename);
	void Release();
	//return texture id = GLuint
	GLuint GetTexture(const string& name);
	void Use(const string& name, GLuint index = 0);

	void loadCubeMap(const string& name, vector<string> faces);
	
};

