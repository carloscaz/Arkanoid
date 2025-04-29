#include "Component.h"

Component::Component() :
	m_active(true)
{}

bool Component::GetActive() const
{
	return m_active;
}

void Component::SetActive(bool _value)
{
	m_active = _value;
}
