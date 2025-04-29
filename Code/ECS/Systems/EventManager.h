#pragma once
#include "System.h"
#include <vector>

//Event manager has a vector of all the systems that can receive messages
//Own version of oberver pattern and singleton pattern applied

class EventManager
{
private:
	std::vector<std::shared_ptr<System>> m_systems;

	EventManager();
public:
	static EventManager& GetInstance();

	void AddSystem(std::shared_ptr<System> _system);

	void SendMessage(const Event& _event);
};