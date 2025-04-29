#include "BallSystem.h"
#include "EventManager.h"

std::shared_ptr<BallSystem> BallSystem::m_instance = nullptr;

BallSystem::BallSystem()
	: 
	m_ballsAccelerated(false),
	m_ballsDecelerated(false)
{}

BallSystem::BallSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager),
	m_ballsAccelerated(false),
	m_ballsDecelerated(false)
{}

//Singleton instance of the BallSystem
std::shared_ptr<BallSystem> BallSystem::GetInstance()
{
	//If doesn't exist an instance of the ballSystem return a new one
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<BallSystem>(new BallSystem());
	}

	return m_instance;
}

void BallSystem::Tick(double _deltaTime)
{
	//Iterate through all the balls of the component manager
	for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
	{
		if (ball.second.GetActive() == true)
		{
			//If the ball goes under the player position, this ball is going to be deactivated
			if (m_componentManager->GetComponent<TransformComponent>(ball.first).GetPosition().y < 0)
			{
				DeactivateBall(ball);
				bool lastBall = true;

				//Check if are active balls in the game. If not send a NoBallsActive event
				for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
				{
					if (ball.second.GetActive() == true)
					{
						lastBall = false;
						break;
					}
				}

				//If there are any active balls in the level, reduce the player lifes and reset the player and the first ball position
				if (lastBall == true)
				{
					std::pair<EntityID, BallComponent> ball = *m_componentManager->GetBallComponents().begin();
					if (m_componentManager->GetComponent<PlayerComponent>(m_componentManager->GetPlayerComponents().begin()->first).GetPlayerLifes() > 0)
					{
						ActivateBall(*m_componentManager->GetBallComponents().begin());
					}
					EventManager::GetInstance().SendMessage(NoBallsActiveEvent());
					return;
					
				}
			}
		}
	}
}

void BallSystem::ReceiveMessage(const Event& _event)
{
	//Make a dynamic cast to check if the event is a AccelerateBallEvent
	// If it is true, increase the velocity of all balls only if balls are not a maximum speed
	if (const auto* event = dynamic_cast<const AccelerateBallEvent*>(&_event))
	{
		if (m_ballsAccelerated == false && m_ballsDecelerated == true)
		{
			for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
			{
				AccelerateBall(ball);
			}
			m_ballsDecelerated = false;
		}

		else if (m_ballsAccelerated == false && m_ballsDecelerated == false)
		{
			for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
			{
				AccelerateBall(ball);
			}
			m_ballsAccelerated = true;
		}
	}

	//Make a dynamic cast to check if the event is a DecelerateBallEvent
	//If it is true, decrease the velocity of all balls only if balls are not a minimum speed
	else if (const auto* event = dynamic_cast<const DecelerateBallEvent*>(&_event))
	{
		if (m_ballsAccelerated == true && m_ballsDecelerated == false)
		{
			for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
			{
				DecelerateBall(ball);
			}
			m_ballsAccelerated = false;
		}

		else if (m_ballsAccelerated == false && m_ballsDecelerated == false)
		{
			for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
			{
				DecelerateBall(ball);
			}
			m_ballsDecelerated = true;
		}
	}

	//Make a dynamic cast to check if the event is a NoMoreBricksEvent
	//If it is true, deactivate all the active balls in the level and activate the first ball
	else if (const auto* event = dynamic_cast<const NoMoreBricksEvent*>(&_event))
	{
		for (std::pair<const EntityID, BallComponent>& ball : m_componentManager->GetBallComponents())
		{
			DeactivateBall(ball);
		}

		ActivateBall(*m_componentManager->GetBallComponents().begin());
	}

}

//Activate a ball in the init position of the ball component
void BallSystem::ActivateBall(std::pair<const EntityID, BallComponent>& ball)
{
	ball.second.SetActive(true);
	m_componentManager->GetComponent<RenderComponent>(ball.first).SetActive(true);
	m_componentManager->GetComponent<TransformComponent>(ball.first).SetPosition(ball.second.GetInitPos());
	m_componentManager->GetComponent<RigidBody>(ball.first).SetActive(true);
	m_componentManager->GetComponent<RigidBody>(ball.first).SetVelocity(glm::vec2(0, 150));
	m_componentManager->GetComponentPointer<CircleCollider>(ball.first)->SetActive(true);
}

//Deactivate a ball and return to the init position of the ball component
void BallSystem::DeactivateBall(std::pair<const EntityID, BallComponent>& ball)
{
	ball.second.SetActive(false);
	m_componentManager->GetComponent<RenderComponent>(ball.first).SetActive(false);
	m_componentManager->GetComponent<TransformComponent>(ball.first).SetPosition(ball.second.GetInitPos());
	m_componentManager->GetComponent<RigidBody>(ball.first).SetActive(false);
	m_componentManager->GetComponentPointer<CircleCollider>(ball.first)->SetActive(false);
}

//Increase the velocity of the ball
void BallSystem::AccelerateBall(std::pair<const EntityID, BallComponent>& ball)
{
	glm::vec2 newVelocity = m_componentManager->GetComponent<RigidBody>(ball.first).GetVelocity();
	newVelocity *= 1.5f;
	m_componentManager->GetComponent<RigidBody>(ball.first).SetVelocity(newVelocity);
}

//Decrease the velocity of the ball
void BallSystem::DecelerateBall(std::pair<const EntityID, BallComponent>& ball)
{
	glm::vec2 newVelocity = m_componentManager->GetComponent<RigidBody>(ball.first).GetVelocity();
	newVelocity /= 1.5f;
	m_componentManager->GetComponent<RigidBody>(ball.first).SetVelocity(newVelocity);
}
