#include "PowerUpSystem.h"
#include <memory>
#include <iostream>

std::shared_ptr<PowerUpSystem> PowerUpSystem::m_instance = nullptr;

PowerUpSystem::PowerUpSystem(std::shared_ptr<ComponentManager> _componentManager) :
	System(_componentManager)
{}

//Singleton instance of the PowerUpSystem
std::shared_ptr<PowerUpSystem> PowerUpSystem::GetInstance()
{
	//if doesn't exist an instance of the PowerUpSystem return a new one
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<PowerUpSystem>(new PowerUpSystem());
	}

	return m_instance;
}

void PowerUpSystem::Tick(double _deltaTime)
{
	//Iterate through all the powerups of the component manager
	for (std::pair<const EntityID, std::shared_ptr<PowerUpComponent>>& powerUp : m_componentManager->GetPowerUpsComponents())
	{
		//Get the ID from the first element of the unordered map pair
		EntityID id = powerUp.first;

		//If the powerUp reach the bottom of the screen, deactivate the powerup
		if (m_componentManager->GetComponent<TransformComponent>(id).GetPosition().y < 0)
		{
			DeactivatePowerUp(id);
		}
	}
}

void PowerUpSystem::ReceiveMessage(const Event& _event)
{
	//Make a dynamic cast to check if the event is a AddNewBallEvent
	//If it is true, add a new ball in the level and deactivate the powerup
	if (const auto* event = dynamic_cast<const AddNewBallEvent*>(&_event))
	{
		for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
		{
			DeactivatePowerUp(event->GetEventComponent());
			if (ball.second.GetActive() == false)
			{
				ActivateBall(ball);

				break;
			}
		}

	}

	//Make a dynamic cast to check if the event is a AccelerateBallEvent
	//If it is true, deactivate the current the powerup
	else if (const auto* event = dynamic_cast<const AccelerateBallEvent*>(&_event))
	{
		DeactivatePowerUp(event->GetEventComponent());
	}

	//Make a dynamic cast to check if the event is a DecelerateBallEvent
	//If it is true, deactivate the current the powerup
	else if (const auto* event = dynamic_cast<const DecelerateBallEvent*>(&_event))
	{
		DeactivatePowerUp(event->GetEventComponent());
	}

	//Make a dynamic cast to check if the event is a BrickDestroyedEvent
	//If it is true, generate a random powerup in the brick position
	else if (const auto* event = dynamic_cast<const BrickDestroyedEvent*>(&_event))
	{
		//Generate a random number between 1 and 10. If its greater than 5 activate a random powerup
		srand(time(NULL));
		unsigned int random_integer = 1 + rand() % 10;
		if (random_integer > 5)
		{
			unsigned int maxSize = m_componentManager->GetPowerUpsComponents().size();
			if (maxSize > 0)
			{
				unsigned int poweUpSelector = 0 + rand() % maxSize;

				std::unordered_map<EntityID, std::shared_ptr<PowerUpComponent>>::iterator it = m_componentManager->GetPowerUpsComponents().begin();

				//Generate a random powerup
				switch (poweUpSelector)
				{
				case 1:
					std::advance(it, 1);
					break;

				case 2:
					std::advance(it, 2);
					break;

				default:
					break;
				}

				std::shared_ptr<PowerUpComponent> powerUpComp = m_componentManager->GetComponentPointer<PowerUpComponent>(it->first);
				if (powerUpComp->GetActive() == false)
				{
					ActivatePowerUp(it->first, event->GetBrickPosition());
					return;
				}
			}
		}
	}
}

//Activate a ball in the init position of the ball component
void PowerUpSystem::ActivateBall(std::pair<const EntityID, BallComponent>& ball)
{
	ball.second.SetActive(true);
	m_componentManager->GetComponent<RenderComponent>(ball.first).SetActive(true);
	m_componentManager->GetComponent<TransformComponent>(ball.first).SetPosition(ball.second.GetInitPos());
	m_componentManager->GetComponent<RigidBody>(ball.first).SetActive(true);
	glm::vec2 newVel = glm::vec2(0, 1);
	newVel *= glm::length(m_componentManager->GetComponent<RigidBody>(ball.first).GetVelocity());
	m_componentManager->GetComponent<RigidBody>(ball.first).SetVelocity(newVel);
	m_componentManager->GetComponentPointer<CircleCollider>(ball.first)->SetActive(true);
}

//Deactivate a ball and return to the init position of the ball component
void PowerUpSystem::DeactivateBall(std::pair<const EntityID, BallComponent>& ball)
{
	ball.second.SetActive(false);
	m_componentManager->GetComponent<RenderComponent>(ball.first).SetActive(false);
	m_componentManager->GetComponent<TransformComponent>(ball.first).SetPosition(ball.second.GetInitPos());
	m_componentManager->GetComponent<RigidBody>(ball.first).SetActive(false);
	m_componentManager->GetComponentPointer<CircleCollider>(ball.first)->SetActive(false);
}

//Deactivate a powerup and return to the init position of the powerup component
void PowerUpSystem::ActivatePowerUp(EntityID _id, glm::vec2& _position)
{
	m_componentManager->GetComponent<RenderComponent>(_id).SetActive(true);
	m_componentManager->GetComponent<TransformComponent>(_id).SetPosition(_position);
	m_componentManager->GetComponent<RigidBody>(_id).SetActive(true);
	m_componentManager->GetComponentPointer<CircleCollider>(_id)->SetActive(true);
	m_componentManager->GetComponentPointer<PowerUpComponent>(_id)->SetActive(true);

}

//Deactivate a powerup and return to the init position of the powerup component
void PowerUpSystem::DeactivatePowerUp(EntityID _id)
{
	m_componentManager->GetComponent<RenderComponent>(_id).SetActive(false);
	m_componentManager->GetComponent<TransformComponent>(_id).SetPosition(glm::vec2(400, 300));
	m_componentManager->GetComponent<RigidBody>(_id).SetActive(false);
	m_componentManager->GetComponentPointer<CircleCollider>(_id)->SetActive(false);
	m_componentManager->GetComponentPointer<PowerUpComponent>(_id)->SetActive(false);

}
