#include "EntityManager.h"

EntityManager::EntityManager() :
	m_entityCount(0)
{}

EntityManager& EntityManager::GetInstance()
{
	static EntityManager instance;
	return instance;
}

void EntityManager::AddEntity()
{
	m_entityCount++;
}

void EntityManager::AddBall(Entity _id)
{
	m_balls.push_back(_id);
}

void EntityManager::AddBrick(Entity _id)
{
	m_bricks.push_back(_id);
}

void EntityManager::AddHeart(Entity _id)
{
	m_hearts.push_back(_id);
}

void EntityManager::SetPlayer(Entity _id)
{
	m_player = _id;
}

unsigned int EntityManager::GetEntityCount() const
{
	return m_entityCount;
}

