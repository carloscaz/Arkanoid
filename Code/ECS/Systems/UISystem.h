#pragma once
#include "System.h"

class UISystem : public System
{
private:
	static std::shared_ptr<UISystem> m_instance;

	UISystem() {};
	UISystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<UISystem> GetInstance();


	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event);
};