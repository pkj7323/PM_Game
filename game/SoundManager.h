#pragma once
#include "Sound.h"

class SoundManager
{
	SINGLE(SoundManager)
public:
	static void Init();
	static void Release();
};
