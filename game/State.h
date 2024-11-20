#pragma once
class object;
class State
{
public:
	State() = default;
	virtual ~State() = default;

	virtual void enter(object* obj, const std::pair<std::string, int>& event) = 0;
	virtual void update(object* obj) = 0;
	virtual void exit(object* obj, const std::pair<std::string, int>& event) = 0;
	virtual void draw(object* obj) = 0;
};
