#pragma once
#include "object.h"
#include "TimeManager.h"
class Scene
{

public:
	Scene() = default;
	virtual ~Scene();
	void renderQuad();


	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update() = 0; 
	virtual void Render() = 0;

	
	void SetName(const std::string& strName) { m_strName = strName; }
	const string& GetName() { return m_strName; }
	virtual void mouse_motion(int i, int y) = 0;
	virtual void Mouse(int button, int state, int i, int y) = 0;
	virtual void mouse_wheel(int button, int dir, int x, int y) = 0;

	template<typename T>
	T* AddObject()
	{
		auto pObj = std::make_unique<T>();
		T* pObjRaw = pObj.get();
		m_vecObj.push_back(std::move(pObj));
		return pObjRaw;
	}

	template<typename T>
	void DeleteObject(T* obj)
	{
		auto it = std::find_if(m_vecObj.begin(), m_vecObj.end(),
			[obj](const std::unique_ptr<object>& pObj) { return pObj.get() == obj; });

		if (it != m_vecObj.end())
		{
			m_vecDeleteObj.push_back(std::move(*it));
			m_vecObj.erase(it);
		}
	}
	
	void RemoveObject()
	{
		m_vecObj.erase(
			std::remove_if(m_vecObj.begin(), m_vecObj.end(),
				[](const std::unique_ptr<object>& obj) {
					obj->Update();
					if (obj->IsNaturalDead()) {
						return true; // 삭제할 요소
					}
					return false; // 삭제하지 않을 요소
				}),
			m_vecObj.end());
	}

	void DeleteDeleteObject()
	{
		m_vecDeleteObj.erase(
			std::remove_if(m_vecDeleteObj.begin(), m_vecDeleteObj.end(),
				[](const std::unique_ptr<object>& obj) {
					obj->Update();
					if (obj->IsDead()) {
						if (obj->GetTimer() > obj->GetTimeToDie()) {
							return true; // 삭제할 요소
						}
						else {
							obj->SetTimer(obj->GetTimer() + DT);
						}
					}
					return false; // 삭제하지 않을 요소
				}),
			m_vecDeleteObj.end());
	}

protected:
	vector<std::unique_ptr<object>>	m_vecObj;
	vector<std::unique_ptr<object>> m_vecDeleteObj;
	string m_strName;
	GLuint quadVAO = 0;
	GLuint quadVBO;

};

