#pragma once
#include "Sound.h"

class SoundManager
{
	SINGLE(SoundManager)

	unordered_map<string, Sound*> m_sounds;
public:
	void Init();
	void Release();
	void Load();
	void Update();

	void AddSound(const string& name, const char* path, bool loop);
	void Play(const string& name);
	void Pause(const string& name);
	void Resume(const string& name);
	void Stop(const string& name);
	void VolumeUp(const string& name);
	void VolumeDown(const string& name);

};
