#pragma once
#include "object.h"
class Scene
{

public:
	Scene() = default;
	virtual ~Scene();


	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update() = 0; 
	virtual void Render() = 0;

	
	void SetName(const std::string& strName) { m_strName = strName; }
	const string& GetName() { return m_strName; }
	virtual void mouse_motion(int i, int y) = 0;
	virtual void Mouse(int button, int state, int i, int y) = 0;
	virtual void mouse_wheel(int button, int dir, int x, int y) = 0;

protected:
	vector<object*>	m_vecObj;
	vector<object*> m_vecDeleteObj;
	string			m_strName;

	template<typename T>
	T* AddObject()
	{
		T* pObj = new T;
		m_vecObj.push_back(pObj);
		return dynamic_cast<T*>(m_vecObj.back());
	}

	template<typename T>
	void DeleteObject(T* obj)
	{
		for (auto& pObj : m_vecObj)
		{
			if (pObj == obj)
			{
				m_vecDeleteObj.push_back(pObj);
				m_vecObj.erase(std::remove(m_vecObj.begin(), m_vecObj.end(), pObj), m_vecObj.end());
				break;
			}
		}
	}

	template<typename T>
	void DeleteDeleteObject(T* obj)
	{
		for (auto& pObj : m_vecDeleteObj)
		{
			if (pObj == obj)
			{
				m_vecDeleteObj.erase(std::remove(m_vecDeleteObj.begin(), m_vecDeleteObj.end(), pObj), m_vecDeleteObj.end());
				delete pObj;
				break;
			}
		}
	}

	
	
};

