#pragma once
#include "../ComponentManager.h"
#include "System.h"

//Collision system to check collisions in the game
class CollisionSystem : public System
{
private:
	static std::shared_ptr<CollisionSystem> m_instance;

	CollisionSystem() {};
	CollisionSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<CollisionSystem> GetInstance();

	
	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event) {};

	bool CheckCircleBoxCollision(TransformComponent& otherTransformComponent, std::shared_ptr<CircleCollider>& colliderComponent, TransformComponent& transformComponent, std::shared_ptr<BoxCollider>& _boxColliderComponent);
};