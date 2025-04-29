#include "BrickSystem.h"
#include "EventManager.h"

std::shared_ptr<BrickSystem> BrickSystem::m_instance = nullptr;

BrickSystem::BrickSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager)
{}

//Singleton instance of the BrickSystem
std::shared_ptr<BrickSystem> BrickSystem::GetInstance()
{
	//If doesn't exist an instance of the ballSystem return a new one
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<BrickSystem>(new BrickSystem());
	}

	return m_instance;
}

void BrickSystem::Tick(double _deltaTime)
{}

void BrickSystem::ReceiveMessage(const Event& _event)
{
	//Make a dynamic cast to check if the event is a BrickDestroyedEvent
	if (const auto* event = dynamic_cast<const BrickDestroyedEvent*>(&_event))
	{
		m_componentManager->GetComponent<BrickComponent>(event->GetBrickID()).Hit();
		if (m_componentManager->GetComponent<BrickComponent>(event->GetBrickID()).GetLifes() <= 0)
		{
			//Deactivate all the logic components of the brick (render, brick and collision)
			DeactivateBrick(event->GetBrickID());
		}

		//Check if there are active bricks in the game
		for (std::pair<const EntityID, BrickComponent>& brick : m_componentManager->GetBrickComponents())
		{
			if (brick.second.GetActive() == true)
			{
				return;
			}
		}

		//If not reset the level
		EventManager::GetInstance().SendMessage(LoadWinLevelEvent());
		/*for (std::pair<const EntityID, BrickComponent>& brick : m_componentManager->GetBrickComponents())
		{
			ActivateBrick(brick.first);
		}*/
	}

	else if (const auto* event = dynamic_cast<const LoadDeathLevelEvent*>(&_event))
	{
		for (std::pair<const EntityID, BrickComponent>& brick : m_componentManager->GetBrickComponents())
		{
			DeactivateBrick(brick.first);
		}
	}


}

//Activate all the logic components of the brick (render, brick and collision)
void BrickSystem::ActivateBrick(EntityID _id)
{
	m_componentManager->GetComponent<BrickComponent>(_id).SetActive(true);
	m_componentManager->GetComponent<RenderComponent>(_id).SetActive(true);
	m_componentManager->GetComponentPointer<BoxCollider>(_id)->SetActive(true);
}

//Deactivate all the logic components of the brick (render, brick and collision)
void BrickSystem::DeactivateBrick(EntityID _id)
{
	m_componentManager->GetComponent<BrickComponent>(_id).SetActive(false);
	m_componentManager->GetComponent<RenderComponent>(_id).SetActive(false);
	m_componentManager->GetComponentPointer<BoxCollider>(_id)->SetActive(false);
}
