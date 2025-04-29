#include "PlayerSystem.h"
#include "EventManager.h"
#include "../Engine/Engine.h"
#include "../ECS/Entities/EntityManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::shared_ptr<PlayerSystem> PlayerSystem::m_instance = nullptr;

PlayerSystem::PlayerSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager)
{}

//Singleton instance of the playerSystem
std::shared_ptr<PlayerSystem> PlayerSystem::GetInstance()
{
	//If doesn't exist an instance create and return a new
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<PlayerSystem>(new PlayerSystem());
	}

	return m_instance;
}

void PlayerSystem::Tick(double _deltaTime)
{
	//Iterate through all the player components of the component manager
	for (std::pair<const EntityID, PlayerComponent>& pair : m_componentManager->GetPlayerComponents())
	{
		//Get the ID from the first element of the unordered map pair
		EntityID id = pair.first;

		TransformComponent& transformComp = m_componentManager->GetComponent<TransformComponent>(id);
		PlayerComponent& playerComp = m_componentManager->GetComponent<PlayerComponent>(id);

		if (playerComp.GetActive() == true)
		{
			//Inputs control of the main level scene
			if (Engine::GetInstance()->GetActiveScene()->GetSceneType() == SceneType::MainLevel)
			{
				std::shared_ptr<BoxCollider> colliderComp = m_componentManager->GetComponentPointer<BoxCollider>(id);

				glm::vec2 pos = transformComp.GetPosition();

				//Left movement with A key
				if (glfwGetKey(Engine::GetInstance()->GetWindowData()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
				{
					//Multiply the displacement with the deltaTime to make it independent of the machine 
					pos.x -= playerComp.GetPlayerVelocity() * _deltaTime;

					//Player can't go outside from the screen limits
					if ((pos.x - colliderComp->GetSize().x / 2) > 0)
					{
						transformComp.SetPosition(pos);
					}
				}

				//Right movement with D key
				else if (glfwGetKey(Engine::GetInstance()->GetWindowData()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
				{
					//Multiply the displacement with the deltaTime to make it independent of the machine 
					pos.x += playerComp.GetPlayerVelocity() * _deltaTime;

					//Player can't go outside from the screen limits
					if ((pos.x + colliderComp->GetSize().x / 2) < Engine::GetInstance()->GetWindowData()->GetWindowWidth())
					{
						transformComp.SetPosition(pos);
					}
				}
			}
			
			else
			{
				//Inpput controls of the Menu Scenes
				if (glfwGetKey(Engine::GetInstance()->GetWindowData()->GetWindow(), GLFW_KEY_ENTER) == GLFW_PRESS)
				{
					EventManager::GetInstance().SendMessage(CreateMainLevelEvent());
					return;
				}
			}
			
		}
	}
}

void PlayerSystem::ReceiveMessage(const Event& _event)
{
	//Make a dynamic cast to check if the event is a NoBallsActiveEvent
	//If it is true, reset the position of the player, reduce the player life
	if (const auto* event = dynamic_cast<const NoBallsActiveEvent*>(&_event))
	{
		m_componentManager->GetComponent<PlayerComponent>(m_componentManager->GetPlayerComponents().begin()->first).ResetScore();
		m_componentManager->GetComponent<PlayerComponent>(m_componentManager->GetPlayerComponents().begin()->first).ReduceLife();

		if (m_componentManager->GetComponent<PlayerComponent>(m_componentManager->GetPlayerComponents().begin()->first).GetPlayerLifes() > 0)
		{
			m_componentManager->GetComponent<TransformComponent>(m_componentManager->GetPlayerComponents().begin()->first).SetPosition(glm::vec2(400, 50));
		}

		else
		{
			//Send a message to change to the death level scene
			EventManager::GetInstance().SendMessage(LoadDeathLevelEvent());
		}

	}

	//Make a dynamic cast to check if the event is a BrickDestroyedEvent
	//Check if there are bricks active in the scene. If there are no more active bricks, load win menu
	if (const auto* event = dynamic_cast<const BrickDestroyedEvent*>(&_event))
	{
		m_componentManager->GetComponent<PlayerComponent>(m_componentManager->GetPlayerComponents().begin()->first).IncreaseScore();

		for (std::pair<const EntityID, BrickComponent>& pair : m_componentManager->GetBrickComponents())
		{
			if (pair.second.GetActive() == true)
			{
				return;
			}
		}
		m_componentManager->GetComponent<TransformComponent>(m_componentManager->GetPlayerComponents().begin()->first).SetPosition(glm::vec2(400,50));
	}
}

void PlayerSystem::DeactivatePlayer(std::pair<const EntityID, PlayerComponent>& _player)
{
	//_player.second.SetActive(false);
	//m_componentManager->GetComponent<RenderComponent>(_player.first).SetActive(false);
	//m_componentManager->GetComponentPointer<BoxCollider>(_player.first)->SetActive(false);
}
