#pragma once
#include "System.h"
#include "../Entities/EntityManager.h"

class LevelSystem : public System
{
private:
	bool loadNewScene;
	int newSCeneID;
	static std::shared_ptr<LevelSystem> m_instance;

	LevelSystem() {};
	LevelSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<LevelSystem> GetInstance();


	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event);
};


