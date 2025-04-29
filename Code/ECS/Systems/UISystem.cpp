#include "UISystem.h"
#include "../Engine/Engine.h"

std::shared_ptr<UISystem> UISystem::m_instance = nullptr;

UISystem::UISystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager)
{}

std::shared_ptr<UISystem> UISystem::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<UISystem>(new UISystem());
	}

	return m_instance;
}

void UISystem::Tick(double _deltaTime)
{

}

void UISystem::ReceiveMessage(const Event& _event)
{
	if (const auto* event = dynamic_cast<const NoBallsActiveEvent*>(&_event))
	{
		for (std::pair<const EntityID, UIHealthComponent>& healthComponent : m_componentManager->GetUIHealthComponents())
		{
			if (m_componentManager->GetComponent<RenderComponent>(healthComponent.first).GetActive() == true)
			{
				m_componentManager->GetComponent<RenderComponent>(healthComponent.first).SetActive(false);
				return;
			}
		}
	}

	if (const auto* event = dynamic_cast<const LoadDeathLevelEvent*>(&_event))
	{
		for (std::pair<const EntityID, UIHealthComponent>& healthComponent : m_componentManager->GetUIHealthComponents())
		{
			m_componentManager->GetComponent<RenderComponent>(healthComponent.first).SetActive(true);
		}
	}

	if (const auto* event = dynamic_cast<const NoMoreBricksEvent*>(&_event))
	{
		for (std::pair<const EntityID, UIHealthComponent>& healthComponent : m_componentManager->GetUIHealthComponents())
		{
			m_componentManager->GetComponent<RenderComponent>(healthComponent.first).SetActive(true);
			return;
		}
	}
}
