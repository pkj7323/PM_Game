﻿#include "stdafx.h"
#include "SoundManager.h"
SoundManager::SoundManager()
= default;
SoundManager::~SoundManager()
= default;



void SoundManager::Init()
{
    Sound::Init();
	Load();
}

void SoundManager::Release()
{
	Sound::Release();
}

void SoundManager::Load()
{
	AddSound("bgm", "resources/sound/Gravitation_2018_Remix.mp3", false);
}

void SoundManager::Update()
{
	for (auto& sound : m_sounds)
	{
		sound.second->Update();
	}
}

void SoundManager::AddSound(const string& name, const char* path, bool loop)
{
	m_sounds[name] = new Sound(path, loop);
}

void SoundManager::Play(const string& name)
{
	if (m_sounds[name] == nullptr)
	{
		cout << "SoundManager::Play() : 사운드가 딕셔너리에 없음\n";
		return;
	}
	m_sounds[name]->play();
}

void SoundManager::Pause(const string& name)
{
	m_sounds[name]->pause();
}

void SoundManager::Resume(const string& name)
{
	m_sounds[name]->resume();
}

void SoundManager::Stop(const string& name)
{
	m_sounds[name]->stop();
}

void SoundManager::VolumeUp(const string& name)
{
	m_sounds[name]->volumeUp();
}

void SoundManager::VolumeDown(const string& name)
{
	m_sounds[name]->volumeDown();
}
