#pragma once
struct FunctionWrapper;
struct FunctionHash;
class object;
class State;
class StateMachine
{
	object* obj;
	queue<std::pair<string, int>> event_q;
	State* current_state;
	std::unordered_multimap<State*, std::pair<FunctionWrapper, State*>> transition;

	//Idle: { on_conveyor : Move ,leave_conveyor : Idle},
public:
	StateMachine(object* obj);
	~StateMachine();

	void init();
	void start(State* state);
	void Update();
	void draw();
	void add_event(const std::pair<string, int>& event);


	/* {
		Idle: { on_conveyor: Move, leave_conveyor : Idle },
		Move : { leave_conveyor: Idle, on_conveyor : Move},
		}*/
	void set_transitions(const std::unordered_multimap<State*, std::pair<FunctionWrapper, State*>>& transitions);
};
// Function declarations
bool move_event(const std::pair<std::string, int>& event);
bool move_stop_event(const std::pair<std::string, int>& event);
bool time_out_event(const std::pair<std::string, int>& event);