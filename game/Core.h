#pragma once
#include "CameraManager.h"
class Core
{
	SINGLE(Core)
	CameraManager* m_pCameraManager;
public:
	void Init();
	void Progress();
	void Update();
	void Render();
	void Release();
	void SetCamara(CameraManager* pCameraManager) { m_pCameraManager = pCameraManager; }
	CameraManager* GetCameraManager() { return m_pCameraManager; }
	void mouse_motion(int x, int y);
	void Mouse(int button, int state, int x, int y);
	void mouse_wheel(int button, int dir, int x, int y);
};

