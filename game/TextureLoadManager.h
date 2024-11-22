#pragma once
class TextureLoadManager
{
	SINGLE(TextureLoadManager)
private:
	unordered_map<string, GLuint> m_texture;
public:
	void Load(const string& name,const string& filename);
	GLuint Use(const string& name);
	
};

