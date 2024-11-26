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
};

