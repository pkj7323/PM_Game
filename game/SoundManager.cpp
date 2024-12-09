#include "stdafx.h"
#include "SoundManager.h"
SoundManager::SoundManager()
= default;
SoundManager::~SoundManager()
= default;


void SoundManager::Init()
{
    Sound::Init();
}

void SoundManager::Release()
{
	Sound::Release();
}
