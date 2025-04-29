#pragma once
#include "../ComponentManager.h"
#include "System.h"

//Render system to render in the screen all the active render components
class RenderSystem : public System
{
private:
	static std::shared_ptr<RenderSystem> m_instance;

	RenderSystem();
	RenderSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<RenderSystem> GetInstance();


	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event) {};
};