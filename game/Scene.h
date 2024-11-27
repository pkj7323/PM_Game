#pragma once
class object;
class Scene
{

public:
	Scene() = default;
	virtual ~Scene();
	//그러나 소멸자는 가상함수로 만들어야한다. 가상 함수로 만들면 자식 클래스의 소멸자가 호출된다.
	//왜? -> 자식 클래스가 소멸자를 호출 햇을 때 부모 클래스의 소멸자가 호출되지 않는다. 그래서 가상함수로 만들어야한다.

	virtual void Enter() = 0;
	virtual void Exit() = 0;	//순수 가상함수로 만들어서 상속받은 클래스에서 구현하도록 한다.

	virtual void Update() = 0; //업데이트를 강제할 필요성이 없을 수도 있다.
	virtual void Render() = 0;	//렌더링을 강제할 필요성이 없을 수도 있다.

	
	inline void SetName(const std::string& strName) { m_strName = strName; }
	const string& GetName() { return m_strName; }
	virtual void mouse_motion(int i, int y) = 0;
	virtual void Mouse(int button, int state, int i, int y) = 0;
	virtual void mouse_wheel(int button, int dir, int x, int y) = 0;

protected:
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

private:
	vector<object*>	m_vecObj;
	string			m_strName;
	
};

