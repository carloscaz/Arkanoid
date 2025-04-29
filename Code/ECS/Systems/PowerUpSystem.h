#pragma once
#include "../ComponentManager.h"
#include "System.h"

class PowerUpSystem : public System
{
private:
	static std::shared_ptr<PowerUpSystem> m_instance;

	PowerUpSystem() {};
	PowerUpSystem(std::shared_ptr<ComponentManager> _componentManager);
public:

	static std::shared_ptr<PowerUpSystem> GetInstance();

	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event);

	void ActivateBall(std::pair<const EntityID, BallComponent>& ball);
	void DeactivateBall(std::pair<const EntityID, BallComponent>& ball);
	void ActivatePowerUp(EntityID _id, glm::vec2& _position);
	void DeactivatePowerUp(EntityID _id);

};