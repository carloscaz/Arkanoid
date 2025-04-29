#pragma once
#include "../ComponentManager.h"
#include "System.h"

class BallSystem : public System
{
private:
	bool m_ballsAccelerated;
	bool m_ballsDecelerated;

	static std::shared_ptr<BallSystem> m_instance;

	BallSystem();
	BallSystem(std::shared_ptr<ComponentManager> _manager);
public:

	static std::shared_ptr<BallSystem> GetInstance();


	void Tick(double _deltaTime) override;
	void ReceiveMessage(const Event& _event);

	void AccelerateBall(std::pair<const EntityID, BallComponent>& ball);
	void DecelerateBall(std::pair<const EntityID, BallComponent>& ball);

	void ActivateBall(std::pair<const EntityID, BallComponent>& ball);
	void DeactivateBall(std::pair<const EntityID, BallComponent>& ball);
};