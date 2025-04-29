#include "../ComponentManager.h"
#include <iostream>

ComponentManager::ComponentManager()
{
	std::cout << "Component Manager Created" << std::endl; 
}

ComponentManager::~ComponentManager()
{
	std::cout << "Component Manager destroyed" << std::endl;
}

ComponentManager& ComponentManager::GetInstance()
{
	static ComponentManager instance;
	return instance;
}

std::unordered_map<EntityID, RenderComponent>& ComponentManager::GetRenderComponents()
{
	return m_renderComponents;
}

std::unordered_map<EntityID, RigidBody>& ComponentManager::GetRigidBodies()
{
	return m_rigidBodies;
}

std::unordered_map<EntityID, std::shared_ptr<Collider>>& ComponentManager::GetCollidersComponents()
{
	return m_colliders;
}

std::unordered_map<EntityID, PlayerComponent>& ComponentManager::GetPlayerComponents()
{
	return m_playerComponents;
}

std::unordered_map<EntityID, BrickComponent>& ComponentManager::GetBrickComponents()
{
	return m_brickComponents;
}

std::unordered_map<EntityID, std::shared_ptr<PowerUpComponent>>& ComponentManager::GetPowerUpsComponents()
{
	return m_powerUps;
}

std::unordered_map<EntityID, BallComponent>& ComponentManager::GetBallComponents()
{
	return m_ballComponents;
}

std::unordered_map<EntityID, UIHealthComponent>& ComponentManager::GetUIHealthComponents()
{
	return m_UIHealthComponents;
}
