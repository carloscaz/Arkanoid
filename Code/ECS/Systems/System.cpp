#include "System.h"

System::System(std::shared_ptr<ComponentManager> _componentManager) :
	m_componentManager(_componentManager)
{}

void System::SetComponentManager(std::shared_ptr<ComponentManager>&_manager)
{
	m_componentManager = _manager;
}
