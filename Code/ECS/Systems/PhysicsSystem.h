#pragma once
#include "../ComponentManager.h"
#include "System.h"

//Physics system to control the physics of the rigidbodies
class PhysicsSystem : public System
{
private:
	static std::shared_ptr<PhysicsSystem> m_instance;

	PhysicsSystem() {};
	PhysicsSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<PhysicsSystem> GetInstance();

	
	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event) {};
};