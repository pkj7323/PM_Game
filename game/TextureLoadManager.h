#pragma once
class TextureLoadManager
{
	SINGLE(TextureLoadManager)
private:
	unordered_map<string, GLuint> m_texture;
public:
	void Load(const string& name,const string& filename);
	void Use(const string& name);
	
};

