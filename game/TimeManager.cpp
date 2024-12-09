#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
= default;
TimeManager::~TimeManager()
= default;

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

void TimeManager::Render()
{
    wchar_t szFPS[64] = L"";
    swprintf_s(szFPS, L"FPS : %f DeltaTime: %f\n", FPS, deltaTime);
    HWND hwnd = GetActiveWindow();
    //HDC hdc = GetDC(hwnd);

    //if (hdc)
    //{
    //    SetBkMode(hdc, TRANSPARENT); // Set background mode to transparent
    //    TextOut(hdc, 10, 10, szFPS, wcslen(szFPS));
    //    ReleaseDC(hwnd, hdc);
    //}
    SetWindowText(hwnd, szFPS);
}
