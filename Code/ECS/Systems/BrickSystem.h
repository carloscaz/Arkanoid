#pragma once
#include "../ComponentManager.h"
#include "System.h"

//Collision system to check collisions in the game
class BrickSystem : public System
{
private:
	static std::shared_ptr<BrickSystem> m_instance;

	BrickSystem() {};
	BrickSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<BrickSystem> GetInstance();


	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event);

	void ActivateBrick(EntityID _id);
	void DeactivateBrick(EntityID _id);
};