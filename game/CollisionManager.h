#pragma once
class object;
class CollisionManager
{
	SINGLE(CollisionManager)
public:
	void Init();
	void Update();
	void AddObject(const string& group, object* a, object* b);
	void RemoveObject(object* obj);
	bool CollisionCheck(const string& group, object* left, object* right);

private:
	std::unordered_map<object*, std::unordered_map<object*, bool>> previousCollisions;
	unordered_map<string, vector<vector<object*>>> CollisionMap;
};

