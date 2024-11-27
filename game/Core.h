#pragma once
#include "Camera.h"
class Core
{
	SINGLE(Core)
	Camera* m_pCameraManager;
public:
	void Init();
	void Progress();
	void Update();
	void Render();
	void Release();
	void SetCamara(Camera* pCameraManager) { m_pCameraManager = pCameraManager; }
	Camera* GetCameraManager() { return m_pCameraManager; }
	void mouse_motion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void mouse_wheel(int button, int dir, int x, int y);
};

