#include "PhysicsSystem.h"
#include "../Engine/Engine.h"

std::shared_ptr<PhysicsSystem> PhysicsSystem::m_instance = nullptr;

PhysicsSystem::PhysicsSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager)
{}

//Singleton instance of the PhysicsSystem
std::shared_ptr<PhysicsSystem> PhysicsSystem::GetInstance()
{
	//If doesn't exist an instance of the Physics System return a new one
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<PhysicsSystem>(new PhysicsSystem());
	}

	return m_instance;
}

void PhysicsSystem::Tick(double _deltaTime)
{
	//Iterate through all the rigidbodies of the component manager
	for (std::pair<const EntityID, RigidBody>& pair : m_componentManager->GetRigidBodies())
	{
		//Get the ID from the first element of the unordered map pair
		EntityID id = pair.first;

		TransformComponent& t = m_componentManager->GetComponent<TransformComponent>(id);
		RigidBody& r = m_componentManager->GetComponent<RigidBody>(id);

		if (r.GetActive() == true)
		{
			//Update the position of the entity with the velocity data of the rigidbody
			//Multiply the displacement with the deltaTime to make it independent of the machine 
			glm::vec2 pos = t.GetPosition();
			pos.x += r.GetVelocity().x * _deltaTime;
			pos.y += r.GetVelocity().y * _deltaTime;

			t.SetPosition(pos);
		}

	}
}
