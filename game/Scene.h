#pragma once
class object;
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
	vector<std::pair<object*, float>> m_vecDeleteObj;
	string			m_strName;

	template<typename T>
	T* AddObject()
	{
		T* pObj = new T;
		m_vecObj.push_back(pObj);
		return dynamic_cast<T*>(m_vecObj.back());
	}

	template<typename T>
	void DeleteObject(T* object)
	{
		auto iter = m_vecObj.begin();
		for (; iter != m_vecObj.end(); ++iter)
		{
			if (*iter == object)
			{
				delete* iter;
				m_vecObj.erase(iter);
				break;
			}
		}
	}
	template<typename T>
	void AddDeleteObj(T* obj, float fTime)
	{
		std::pair<object*, float> pair = std::make_pair(obj, fTime);
		m_vecDeleteObj.push_back(pair);
	}


	
	
};

