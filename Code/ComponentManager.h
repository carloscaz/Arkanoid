#pragma once
#include "../ECS/Entities/Entity.h"
#include "../ECS/Components/TransformComponent/TransformComponent.h"
#include "../ECS/Components/RenderComponent/RenderComponent.h"
#include "../ECS/Components/RigidBody/RigidBody.h"
#include "../ECS/Components/Colliders/Colliders.h"
#include "../ECS/Components/PlayerComponent/PlayerComponent.h"
#include "../ECS/Components/BrickComponent/BrickComponent.h"
#include "../ECS/Components/PowerUpComponent/PowerUpComponent.h"
#include "../ECS/Components/BallComponent/BallComponent.h"
#include "../ECS/Components/UIHealthComponent/UIHealthComponent.h"

#include <unordered_map>

class Component;
//Component manager with multiple maps for each component type
class ComponentManager
{
private:
	//Component containers
	std::unordered_map<EntityID, TransformComponent> m_transformComponents;
	std::unordered_map<EntityID, RenderComponent> m_renderComponents;
	std::unordered_map<EntityID, RigidBody> m_rigidBodies;
	std::unordered_map<EntityID, std::shared_ptr<Collider>> m_colliders;
	std::unordered_map<EntityID, PlayerComponent> m_playerComponents;
	std::unordered_map<EntityID, BrickComponent> m_brickComponents;
	std::unordered_map<EntityID, std::shared_ptr<PowerUpComponent>> m_powerUps;
	std::unordered_map<EntityID, BallComponent> m_ballComponents;
	std::unordered_map<EntityID, UIHealthComponent> m_UIHealthComponents;

public:
	ComponentManager();
	~ComponentManager();

	static ComponentManager& GetInstance();

	//Add any valid component to the manager
	template <typename T>
	void AddComponent(EntityID _id, T& _component);

	//Get any valid component from the manager
	template <typename T>
	T& GetComponent(EntityID _id);

	//Get a shared pointer of a component
	template <typename T>
	std::shared_ptr<T> GetComponentPointer(EntityID _id);

	//Bool fuction to check if an entity has a component
	template<typename T>
	bool HasComponent(EntityID _id);

	std::unordered_map<EntityID, RenderComponent>& GetRenderComponents();
	std::unordered_map<EntityID, RigidBody>& GetRigidBodies();
	std::unordered_map<EntityID, std::shared_ptr<Collider>>& GetCollidersComponents();
	std::unordered_map<EntityID, PlayerComponent>& GetPlayerComponents();
	std::unordered_map<EntityID, BrickComponent>& GetBrickComponents();
	std::unordered_map<EntityID, std::shared_ptr<PowerUpComponent>>& GetPowerUpsComponents();
	std::unordered_map<EntityID, BallComponent>& GetBallComponents();
	std::unordered_map<EntityID, UIHealthComponent>& GetUIHealthComponents();
};

//Add any valid component to the manager
template<typename T>
inline void ComponentManager::AddComponent(EntityID _id, T& _component)
{
	if constexpr (std::is_same_v <T, TransformComponent>)
	{
		m_transformComponents[_id] = _component;
	}

	else if constexpr (std::is_same_v <T, RenderComponent>)
	{
		m_renderComponents[_id] = _component;
	}

	else if constexpr (std::is_same_v <T, RigidBody>)
	{
		m_rigidBodies[_id] = _component;
	}

	else if constexpr (std::is_same_v<T, CircleCollider> || std::is_same_v<T, BoxCollider>)
	{
		m_colliders[_id] = std::make_shared<T>(_component);
	}

	else if constexpr (std::is_same_v <T, PlayerComponent>)
	{
		m_playerComponents[_id] = _component;
	}

	else if constexpr (std::is_same_v <T, BrickComponent>)
	{
		m_brickComponents[_id] = _component;
	}

	else if constexpr (std::is_same_v <T, BallComponent>)
	{
		m_ballComponents[_id] = _component;
	}

	else if constexpr (std::is_same_v <T, AddBallPowerUpComponent> || std::is_same_v <T, AccelerateBallPowerUp> || std::is_same_v <T, DecelerateBallPowerUp>)
	{
		m_powerUps[_id] = std::make_shared<T>(_component);
	}

	else if constexpr (std::is_same_v <T, UIHealthComponent>)
	{
		m_UIHealthComponents[_id] = _component;
	}
}

//Get any valid component from the manager
template<typename T>
inline T& ComponentManager::GetComponent(EntityID _id)
{
	if constexpr (std::is_same_v <T, TransformComponent>)
	{
		return m_transformComponents[_id];
	}

	else if constexpr (std::is_same_v<T, RenderComponent>)
	{
		return m_renderComponents[_id];
	}

	else if constexpr (std::is_same_v<T, RigidBody>)
	{
		return m_rigidBodies[_id];
	}

	else if constexpr (std::is_same_v<T, CircleCollider> || std::is_same_v<T, BoxCollider>)
	{
		return m_colliders[_id];
	}

	else if constexpr (std::is_same_v<T, PlayerComponent>)
	{
		return m_playerComponents[_id];
	}

	else if constexpr (std::is_same_v<T, BrickComponent>)
	{
		return m_brickComponents[_id];
	}

	else if constexpr (std::is_same_v<T, BallComponent>)
	{
		return m_ballComponents[_id];
	}

	else if constexpr (std::is_same_v<T, UIHealthComponent>)
	{
		return m_UIHealthComponents[_id];
	}
}

//Get a shared pointer of a component
template<typename T>
inline std::shared_ptr<T> ComponentManager::GetComponentPointer(EntityID _id)
{
	if constexpr (std::is_same_v<T, CircleCollider> || std::is_same_v<T, BoxCollider>)
	{
		return std::dynamic_pointer_cast<T>(m_colliders[_id]);
	}

	else if constexpr (std::is_same_v<T, PowerUpComponent>)
	{
		return std::dynamic_pointer_cast<T>(m_powerUps[_id]);
	}
	else
	{
		return nullptr; // Caso seguro si no coincide el tipo
	}
}

//Bool fuction to check if an entity has a component
template<typename T>
inline bool ComponentManager::HasComponent(EntityID _id)
{
	if constexpr (std::is_same_v <T, PlayerComponent>)
	{
		if (m_playerComponents.find(_id) != m_playerComponents.end())
		{
			return true;
		}
	}

	else if constexpr (std::is_same_v <T, BrickComponent>)
	{
		if (m_brickComponents.find(_id) != m_brickComponents.end())
		{
			return true;
		}
	}

	else if constexpr (std::is_same_v <T, PowerUpComponent>)
	{
		if (m_powerUps.find(_id) != m_powerUps.end())
		{
			return true;
		}
	}
	return false;
}
