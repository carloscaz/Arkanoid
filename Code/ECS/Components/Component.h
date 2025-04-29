#pragma once
class Component
{
protected:
	bool m_active;
public:
	Component();

	bool GetActive() const;
	void SetActive(bool _value);
};