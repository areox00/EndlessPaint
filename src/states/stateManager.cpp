#include "stateManager.hpp"

#include "state.hpp"

StateManager::StateManager()
{

}

StateManager::~StateManager()
{
	if (state != nullptr)
		delete state;
}

void StateManager::setState(State *state)
{
	if (this->state != nullptr)
		delete this->state;

	this->state = state;
}

State* StateManager::getState()
{
	return state;
}