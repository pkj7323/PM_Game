#pragma once
#include "Scene.h"

class  IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();

	void Enter() override;
	void Exit() override;
	void Update() override;
	void Render() override;
	
};
