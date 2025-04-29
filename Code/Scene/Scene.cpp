#include "Scene.h"
#include <iostream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../Engine/Engine.h"
#include "../ECS/Systems/PhysicsSystem.h"
#include "../ECS/Systems/RenderSystem.h"
#include "../ECS/Systems/CollisionSystem.h"
#include "../ECS/Systems/PlayerSystem.h"
#include "../ECS/Systems/BrickSystem.h"
#include "../ECS/Systems/PowerUpSystem.h"
#include "../ECS/Systems/BallSystem.h"
#include "../ECS/Systems/UISystem.h"
#include "../ECS/Systems/LevelSystem.h"

Scene::Scene()
{

}

ComponentManager& Scene::GetComponentManager()
{
	return m_componentManager;

}

EntityManager& Scene::GetEntitymanager()
{
	return m_entityManager;
}

SceneType Scene::GetSceneType()
{
	return m_sceneType;
}

MenuLevel::MenuLevel()
{
	m_sceneType = SceneType::UIMenu;

	glm::vec2 pos(400, 400);

	TransformComponent t(pos, glm::vec2(0), glm::vec2(0.75f));
	m_componentManager.AddComponent(m_entityManager.GetEntityCount(), t);
	PlayerComponent menuControl;
	m_componentManager.AddComponent(m_entityManager.GetEntityCount(), menuControl);
}

MainMenu::MainMenu() :
	MenuLevel()
{
	//Read the info from the json file
	std::ifstream archivo("Data/Scenes/MainMenu.json");
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	//Create the background image of the menu
	Entity entity = m_entityManager.GetEntityCount();

	CreateBackground(m_entityManager, m_componentManager, doc["backgroundTexture"].GetString());


	//Add the created entity
	m_entityManager.AddEntity();

	//Set all the systems of the scene
	std::shared_ptr<ComponentManager> componentManager = std::make_shared<ComponentManager>(m_componentManager);
	PlayerSystem::GetInstance()->SetComponentManager(componentManager);
	CollisionSystem::GetInstance()->SetComponentManager(componentManager);
	PhysicsSystem::GetInstance()->SetComponentManager(componentManager);
	RenderSystem::GetInstance()->SetComponentManager(componentManager);
	BrickSystem::GetInstance()->SetComponentManager(componentManager);
	PowerUpSystem::GetInstance()->SetComponentManager(componentManager);
	BallSystem::GetInstance()->SetComponentManager(componentManager);
	UISystem::GetInstance()->SetComponentManager(componentManager);
	LevelSystem::GetInstance()->SetComponentManager(componentManager);

	std::cout << "Main menu scene created" << std::endl;
}

MainMenu::~MainMenu()
{
	std::cout << "Main menu scene destroyed" << std::endl;
}

MainLevel::MainLevel()
{
	m_sceneType = SceneType::MainLevel;

	//Read the info from the json file
	std::ifstream archivo("Data/Scenes/MainLevel.json");
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	CreateBackground(m_entityManager, m_componentManager, doc["backgroundTexture"].GetString());
	m_entityManager.AddEntity();

	CreateBricks(m_entityManager, m_componentManager, "Data/Entities/Brick.json", 5, 7);
	CreateBalls(m_entityManager, m_componentManager, "Data/Entities/Ball.json", 3);
	CreatePlayer(m_entityManager, m_componentManager, "Data/Entities/Player.json");
	CreatePowerUp(m_entityManager, m_componentManager, "Data/Entities/PowerUps.json");
	CreateHealthUI(m_entityManager, m_componentManager, "Data/Entities/HealthIcon.json", 3

	);



	std::shared_ptr<ComponentManager> componentManager = std::make_shared<ComponentManager>(m_componentManager);
	PlayerSystem::GetInstance()->SetComponentManager(componentManager);
	CollisionSystem::GetInstance()->SetComponentManager(componentManager);
	PhysicsSystem::GetInstance()->SetComponentManager(componentManager);
	RenderSystem::GetInstance()->SetComponentManager(componentManager);
	BrickSystem::GetInstance()->SetComponentManager(componentManager);
	PowerUpSystem::GetInstance()->SetComponentManager(componentManager);
	BallSystem::GetInstance()->SetComponentManager(componentManager);
	UISystem::GetInstance()->SetComponentManager(componentManager);
	LevelSystem::GetInstance()->SetComponentManager(componentManager);

	std::cout << "Main level scene loaded" << std::endl;
}

DeathMenu::DeathMenu() :
	MenuLevel()
{
	//Read the info from the json file
	std::ifstream archivo("Data/Scenes/DeathMenu.json");
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	glm::vec2 pos(400, 400);
	Entity entity(m_entityManager.GetEntityCount());

	CreateBackground(m_entityManager, m_componentManager, doc["backgroundTexture"].GetString());

	TransformComponent t(pos, glm::vec2(0), glm::vec2(0.75f));
	m_componentManager.AddComponent(entity.GetID(), t);
	PlayerComponent menuControl;
	m_componentManager.AddComponent(entity.GetID(), menuControl);

	m_entityManager.AddEntity();

	std::shared_ptr<ComponentManager> componentManager = std::make_shared<ComponentManager>(m_componentManager);

	PlayerSystem::GetInstance()->SetComponentManager(componentManager);
	CollisionSystem::GetInstance()->SetComponentManager(componentManager);
	PhysicsSystem::GetInstance()->SetComponentManager(componentManager);
	RenderSystem::GetInstance()->SetComponentManager(componentManager);
	BrickSystem::GetInstance()->SetComponentManager(componentManager);
	PowerUpSystem::GetInstance()->SetComponentManager(componentManager);
	BallSystem::GetInstance()->SetComponentManager(componentManager);
	UISystem::GetInstance()->SetComponentManager(componentManager);
	LevelSystem::GetInstance()->SetComponentManager(componentManager);

	std::cout << "Death menu scene created" << std::endl;
}

DeathMenu::~DeathMenu()
{
	std::cout << "Death menu scene destroyed" << std::endl;
}

WinMenu::WinMenu()
	:
	MenuLevel()
{
	//Read the info from the json file
	std::ifstream archivo("Data/Scenes/WinMenu.json");
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	CreateBackground(m_entityManager, m_componentManager, doc["backgroundTexture"].GetString());

	std::shared_ptr<ComponentManager> componentManager = std::make_shared<ComponentManager>(m_componentManager);
	PlayerSystem::GetInstance()->SetComponentManager(componentManager);
	CollisionSystem::GetInstance()->SetComponentManager(componentManager);
	PhysicsSystem::GetInstance()->SetComponentManager(componentManager);
	RenderSystem::GetInstance()->SetComponentManager(componentManager);
	BrickSystem::GetInstance()->SetComponentManager(componentManager);
	PowerUpSystem::GetInstance()->SetComponentManager(componentManager);
	BallSystem::GetInstance()->SetComponentManager(componentManager);
	UISystem::GetInstance()->SetComponentManager(componentManager);
	LevelSystem::GetInstance()->SetComponentManager(componentManager);

	std::cout << "Win menu scene created" << std::endl;
}

WinMenu::~WinMenu()
{
	std::cout << "Win menu scene destroyed" << std::endl;
}

/*
*	Functions to create all the elements of the main level
*/

void CreateBackground(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename)
{
	//Create the background of the scene
	glm::vec2 pos(400, 300);
	Entity entity(_entityManager.GetEntityCount());
	Texture texture(_filename);

	RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
	_componentManager.AddComponent(entity.GetID(), renderComponent);
	TransformComponent t(pos, glm::vec2(0), glm::vec2(1));
	_componentManager.AddComponent(entity.GetID(), t);
}

void CreateBricks(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename, int _NumRows, int _numColumns)
{
	glm::vec2 pos(150, 300);

	//Read the info from the json file
	std::ifstream archivo(_filename);
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	Texture texture("Data/Textures/Brick.png");
	for (int i = 0; i < _NumRows; ++i)
	{
		for (unsigned int j = 0; j < _numColumns; ++j)
		{
			Entity entity(_entityManager.GetEntityCount());

			RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
			_componentManager.AddComponent(entity.GetID(), renderComponent);

			TransformComponent transform(pos, glm::vec2(0), glm::vec2(1));
			_componentManager.AddComponent(entity.GetID(), transform);

			BoxCollider colliderComponent(glm::vec2(texture.GetWidth(), texture.GetHeight()));
			_componentManager.AddComponent(entity.GetID(), colliderComponent);

			BrickComponent brickComponent(doc["BrickComponent"]["lifes"].GetInt());
			_componentManager.AddComponent(entity.GetID(), brickComponent);

			_entityManager.AddEntity();

			pos.x += texture.GetWidth() + 20;
		}

		pos.x = 150;
		pos.y += texture.GetHeight() + 20;
	};
}

void CreateBalls(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename, int _numBalls)
{
	
	//Read the info from the json file
	std::ifstream archivo(_filename);
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	glm::vec2 pos(doc["TransformComponent"]["positionX"].GetFloat(), doc["TransformComponent"]["positionY"].GetFloat());
	for (int i = 0; i < _numBalls; ++i)
	{
		Entity entity(_entityManager.GetEntityCount());
		Texture texture("Data/Textures/Ball.png");

		TransformComponent transformComponent(pos, glm::vec2(0), glm::vec2(1));
		_componentManager.AddComponent(entity.GetID(), transformComponent);
		if (i == 0)
		{
			RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
			_componentManager.AddComponent(entity.GetID(), renderComponent);

			RigidBody rigidBody(glm::vec2(doc["RigidBody"]["velocityX"].GetFloat(), doc["RigidBody"]["velocityY"].GetFloat()));
			_componentManager.AddComponent(entity.GetID(), rigidBody);

			BallComponent ballComp;
			ballComp.SetActive(true);
			_componentManager.AddComponent(entity.GetID(), ballComp);

			CircleCollider circleColliderComponent(texture.GetWidth() / 2);
			_componentManager.AddComponent(entity.GetID(), circleColliderComponent);
		}

		else
		{
			BallComponent ballComp;
			ballComp.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), ballComp);

			RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
			renderComponent.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), renderComponent);

			RigidBody rigidBody(glm::vec2(doc["RigidBody"]["velocityX"].GetFloat(), doc["RigidBody"]["velocityY"].GetFloat()));
			rigidBody.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), rigidBody);

			CircleCollider circleColliderComponent(texture.GetWidth() / 2);
			circleColliderComponent.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), circleColliderComponent);
		}
		_entityManager.AddEntity();
	};
}

void CreatePlayer(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename)
{
	//Read the info from the json file
	std::ifstream archivo(_filename);
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	glm::vec2 pos(doc["TransformComponent"]["positionX"].GetFloat(), doc["TransformComponent"]["positionY"].GetFloat());
	Entity entity(_entityManager.GetEntityCount());
	Texture texture("Data/Textures/Player.png");

	RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
	_componentManager.AddComponent(entity.GetID(), renderComponent);

	TransformComponent transformComponent(pos, glm::vec2(0), glm::vec2(1));
	_componentManager.AddComponent(entity.GetID(), transformComponent);

	PlayerComponent playerComponent(doc["PlayerComponent"]["speed"].GetFloat());
	_componentManager.AddComponent(entity.GetID(), playerComponent);

	BoxCollider boxColliderComponent(glm::vec2(texture.GetWidth(), texture.GetHeight()));
	_componentManager.AddComponent(entity.GetID(), boxColliderComponent);

	_entityManager.AddEntity();
}

void CreatePowerUp(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename)
{
	//Read the info from the json file
	std::ifstream archivo(_filename);
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	glm::vec2 pos(doc["powerUpPositionX"].GetFloat(), doc["powerUpPositionY"].GetFloat());
	for (int i = 0; i < 3; ++i)
	{
		Entity entity(_entityManager.GetEntityCount());

		if (i == 0)
		{
			Texture texture("Data/Textures/NewBallPowerUp.png");

			RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
			renderComponent.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), renderComponent);

			CircleCollider circleCollider(texture.GetWidth() / 2);
			circleCollider.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), circleCollider);

			AddBallPowerUpComponent powerUpComp;
			powerUpComp.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), powerUpComp);
		}

		else if (i == 1)
		{
			Texture texture("Data/Textures/AccelerateBallPowerUp.png");

			RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
			renderComponent.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), renderComponent);

			CircleCollider b(texture.GetWidth() / 2);
			b.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), b);

			AccelerateBallPowerUp powerUpComp;
			powerUpComp.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), powerUpComp);
		}

		else
		{
			Texture texture("Data/Textures/DecelerateBallPowerUp.png");

			RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
			renderComponent.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), renderComponent);

			CircleCollider circleColliderComp(texture.GetWidth() / 2);
			circleColliderComp.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), circleColliderComp);

			DecelerateBallPowerUp powerUpComp;
			powerUpComp.SetActive(false);
			_componentManager.AddComponent(entity.GetID(), powerUpComp);
		}

		TransformComponent transformComponent(pos, glm::vec2(0), glm::vec2(1));
		_componentManager.AddComponent(entity.GetID(), transformComponent);

		RigidBody rigidBody(glm::vec2(doc["velocityX"].GetFloat(), doc["velocityY"].GetFloat()));
		rigidBody.SetActive(false);
		_componentManager.AddComponent(entity.GetID(), rigidBody);

		_entityManager.AddEntity();
	}

}

void CreateHealthUI(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename, int _numIcons)
{
	//Read the info from the json file
	std::ifstream archivo(_filename);
	if (!archivo.is_open()) {
		std::cout << "Error opening JSON file" << std::endl;
	}

	std::stringstream buffer;
	buffer << archivo.rdbuf();
	std::string jsonContent = buffer.str();

	rapidjson::Document doc;
	doc.Parse(jsonContent.c_str());

	if (doc.HasParseError()) {
		std::cout << "Error reading JSON file" << std::endl;
	}

	glm::vec2 pos(doc["positionX"].GetFloat(), doc["positionY"].GetFloat());
	for (int i = 0; i < 3; i++)
	{
		Entity entity(_entityManager.GetEntityCount());
		Texture texture("Data/Textures/FullHeart.png");

		RenderComponent renderComponent(*Engine::GetInstance()->GetGameShader(), texture);
		_componentManager.AddComponent(entity.GetID(), renderComponent);

		TransformComponent t(pos, glm::vec2(0), glm::vec2(0.75f));
		_componentManager.AddComponent(entity.GetID(), t);

		UIHealthComponent healthComp;
		_componentManager.AddComponent(entity.GetID(), healthComp);

		_entityManager.AddEntity();
		pos.x -= 50;
	}
}


