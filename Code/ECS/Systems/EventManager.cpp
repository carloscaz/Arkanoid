#include "EventManager.h"

EventManager::EventManager()
{}

EventManager& EventManager::GetInstance()
{
	static EventManager instance;
	return instance;
}

void EventManager::AddSystem(std::shared_ptr<System> _system)
{
	m_systems.push_back(_system);
}

//Probably is better to use a template function instead a reference to the event
void EventManager::SendMessage(const Event& _event)
{
	for (std::shared_ptr<System>& system : m_systems)
	{
		system->ReceiveMessage(_event);
	}
}
