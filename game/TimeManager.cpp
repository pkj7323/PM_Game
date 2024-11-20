#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
{
}
TimeManager::~TimeManager()
{
}


void TimeManager::Init()
{
	currentTime = 0;
	lastTime = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
	deltaTime = 0;
}

void TimeManager::Update()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
	deltaTime = currentTime - lastTime;
	FPS = 1 / deltaTime;
	lastTime += deltaTime;
}

float TimeManager::GetDeltaTime()
{
	return deltaTime;
}
