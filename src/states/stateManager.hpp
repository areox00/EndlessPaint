#pragma once

class State;

class StateManager {
private:
	State *state = nullptr;
public:
	StateManager();
	~StateManager();

	void setState(State *state);
	State *getState();
};