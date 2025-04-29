#pragma once
#include "Entity.h"
#include <vector>

//Entity manager of the ECS
class EntityManager
{
private:
	unsigned int m_entityCount;
	std::vector<Entity> m_bricks;
	std::vector<Entity> m_balls;
	std::vector<Entity> m_hearts;
	Entity m_player;

public:
	EntityManager();
	static EntityManager& GetInstance();

	void AddEntity();
	void AddBall(Entity _id);
	void AddBrick(Entity _id);
	void AddHeart(Entity _id);
	void SetPlayer(Entity _id);

	unsigned int GetEntityCount() const;
};