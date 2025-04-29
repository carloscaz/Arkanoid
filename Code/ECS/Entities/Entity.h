#pragma once
#include <memory>

//The ID of the entities is an unsigned integer
using EntityID = unsigned int;

class Entity
{
private:
	EntityID m_id;

public:
	Entity() {};
	Entity(EntityID _id);

	EntityID GetID() const;
};