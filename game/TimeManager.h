#pragma once
class TimeManager
{
	
	SINGLE(TimeManager)
	float currentTime;
	float lastTime;
	float deltaTime;
	float FPS;
public:
	void Init();
	void Update();
	float GetDeltaTime();
};

