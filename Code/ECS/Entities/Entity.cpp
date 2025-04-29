#include "Entity.h"

Entity::Entity(EntityID _id) :
	m_id(_id)
{}

EntityID Entity::GetID() const
{
	return m_id;
}

