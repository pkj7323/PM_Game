#include "stdafx.h"
#include "StateMachine.h"
#include "State.h"





StateMachine::StateMachine(object* obj) : obj{obj},current_state(nullptr)
{
}

StateMachine::~StateMachine()
{
	obj = nullptr;
	current_state = nullptr;
	event_q = {};
	transition = {};
}

void StateMachine::init()
{
}

void StateMachine::start(State* state)
{
	current_state = state;
	current_state->enter(obj, { "START", 0 });
}

void StateMachine::Update()
{
	if (current_state)
	{
		current_state->update(obj);
		if (!event_q.empty())
		{
			auto e = event_q.front();
			event_q.pop();
			auto range = transition.equal_range(current_state);
			for (auto it = range.first; it != range.second; ++it)
			{
				if (it->second.first.func(e))
				{
					current_state->exit(obj, e);
					current_state = it->second.second;
					current_state->enter(obj, e);
					return;
				}
			}
			
			std::cerr << "Warning: No transition for event: " << e.first << std::endl;
		}
	}
}

void StateMachine::draw()
{
	if (current_state)
	{
		current_state->draw(obj);
	}
}

void StateMachine::add_event(const std::pair<std::string, int>& event)
{
	event_q.push(event);
}

void StateMachine::set_transitions(
	const std::unordered_multimap<State*, std::pair<FunctionWrapper, State*>>& transitions)
{
	transition = transitions;
}


bool move_event(const std::pair<std::string, int>& event)
{
	return event.first == "MOVE";
}
bool move_stop_event(const std::pair<std::string, int>& event)
{
	return event.first == "STOP";
}

bool time_out_event(const std::pair<std::string, int>& event)
{
	return event.first == "TIME_OUT";
}
