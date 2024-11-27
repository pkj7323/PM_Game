#pragma once
class object;
class Scene
{

public:
	Scene() = default;
	virtual ~Scene();
	//�׷��� �Ҹ��ڴ� �����Լ��� �������Ѵ�. ���� �Լ��� ����� �ڽ� Ŭ������ �Ҹ��ڰ� ȣ��ȴ�.
	//��? -> �ڽ� Ŭ������ �Ҹ��ڸ� ȣ�� ���� �� �θ� Ŭ������ �Ҹ��ڰ� ȣ����� �ʴ´�. �׷��� �����Լ��� �������Ѵ�.

	virtual void Enter() = 0;
	virtual void Exit() = 0;	//���� �����Լ��� ���� ��ӹ��� Ŭ�������� �����ϵ��� �Ѵ�.

	virtual void Update() = 0; //������Ʈ�� ������ �ʿ伺�� ���� ���� �ִ�.
	virtual void Render() = 0;	//�������� ������ �ʿ伺�� ���� ���� �ִ�.

	
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

