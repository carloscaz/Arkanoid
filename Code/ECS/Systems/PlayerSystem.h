#pragma once
#include "../ComponentManager.h"
#include "System.h"

//Player system to control the player movement in the game
class PlayerSystem : public System
{
private:
	static std::shared_ptr<PlayerSystem> m_instance;

	PlayerSystem() {};
	PlayerSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<PlayerSystem> GetInstance();
	
	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event);

	void DeactivatePlayer(std::pair<const EntityID, PlayerComponent>& _player);
};