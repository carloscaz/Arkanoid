#pragma once
#include "../ComponentManager.h"
#include "Event.h"

class System
{
protected:
	std::shared_ptr<ComponentManager> m_componentManager;

protected:
	System() {};
	System(std::shared_ptr<ComponentManager> _componentManager);

	virtual void Tick(double _deltaTime) = 0;

public:
	virtual void SetComponentManager(std::shared_ptr<ComponentManager>& _manager);
	virtual void ReceiveMessage(const Event& _event) = 0;
};