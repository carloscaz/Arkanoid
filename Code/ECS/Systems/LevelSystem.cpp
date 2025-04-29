#include "LevelSystem.h"
#include "../Scene/Scene.h"
#include "../Engine/Engine.h"

std::shared_ptr<LevelSystem> LevelSystem::m_instance = nullptr;

LevelSystem::LevelSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager),
	loadNewScene(false)
{}

//Singleton instance of the LevelSystem
std::shared_ptr<LevelSystem> LevelSystem::GetInstance()
{
	//If doesn't exist an instance of the LevelSystem return a new one
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<LevelSystem>(new LevelSystem());
	}

	return m_instance;
}

void LevelSystem::Tick(double _deltaTime)
{
	if (loadNewScene == true)
	{
		switch (newSCeneID)
		{
		case 0:
			//Create a new Main Menu Scene
			Engine::GetInstance()->SetActiveScene(std::make_shared<MainMenu>());
			break;

		case 1:
			//Create a new Main Level Scene
			Engine::GetInstance()->SetActiveScene(std::make_shared<Scene>(MainLevel()));
			break;

		case 2:
			//Create a new Win Menu Scene
			Engine::GetInstance()->SetActiveScene(std::make_shared<Scene>(DeathMenu()));
			break;

		case 3:
			//Create a new Death Menu Scene
			Engine::GetInstance()->SetActiveScene(std::make_shared<Scene>(WinMenu()));
			break;
		}

		EntityManager& entityManager = Engine::GetInstance()->GetActiveScene()->GetEntitymanager();
		ComponentManager& componentManager = Engine::GetInstance()->GetActiveScene()->GetComponentManager();
		loadNewScene = false;
	}
}

void LevelSystem::ReceiveMessage(const Event& _event)
{
	//Activate the creation of a new scene

	//Create a new Main Menu Scene
	if (const auto* event = dynamic_cast<const CreateMainMenuEvent*>(&_event))
	{
		loadNewScene = true;
		newSCeneID = 0;
	}

	//Create a new Main Level Scene
	else if (const auto* event = dynamic_cast<const CreateMainLevelEvent*>(&_event))
	{
		loadNewScene = true;
		newSCeneID = 1;
	}

	//Create a new Win Menu Scene
	else if (const auto* event = dynamic_cast<const LoadDeathLevelEvent*>(&_event))
	{
		loadNewScene = true;
		newSCeneID = 2;
	}

	//Create a new Death Menu Scene
	else if (const auto* event = dynamic_cast<const LoadWinLevelEvent*>(&_event))
	{
		loadNewScene = true;
		newSCeneID = 3;
	}

}
