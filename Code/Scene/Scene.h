#pragma once
#include "../ComponentManager.h"
#include "../ECS/Entities/EntityManager.h"

#include <rapidjson/document.h>

enum class SceneType
{
	MainLevel,
	UIMenu
};

//Base class of a scene
class Scene
{
protected:
	rapidjson::Document doc;

	ComponentManager m_componentManager;
	EntityManager m_entityManager;
	SceneType m_sceneType;

public:
	Scene();

	ComponentManager& GetComponentManager();
	EntityManager& GetEntitymanager();

	SceneType GetSceneType();
};

//Child class to menu scenes
class MenuLevel : public Scene
{
public:
	MenuLevel();
};
class MainLevel : public Scene
{

public:
	MainLevel();
};

//Child class to main menu scene
class MainMenu : public MenuLevel
{
public:
	MainMenu();
	~MainMenu();
};

//Child class to win menu scene
class WinMenu : public MenuLevel
{
public:
	WinMenu();
	~WinMenu();
};

//Child claass to death menu
class DeathMenu : public MenuLevel
{
public:
	DeathMenu();
	~DeathMenu();
};


void CreateBackground(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename);
void CreateBricks(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename, int _NumRows, int _numColumns);
void CreateBalls(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename, int _numBalls);
void CreatePlayer(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename);
void CreatePowerUp(EntityManager& _entityManager, ComponentManager& , const char* _filename);
void CreateHealthUI(EntityManager& _entityManager, ComponentManager& _componentManager, const char* _filename, int _numIcons);