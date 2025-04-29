#pragma once
class Event
{
public:
	Event() {};
	virtual ~Event() = default;
};

class NoBallsActiveEvent : public Event
{ 
public:
	NoBallsActiveEvent() {};
};

class AddNewBallEvent : public Event
{
private:
	EntityID m_IDEventDispatcher;
public:
	AddNewBallEvent(EntityID _id) : m_IDEventDispatcher(_id) {};

	EntityID GetEventComponent() const { return m_IDEventDispatcher; };
};

class AccelerateBallEvent : public Event
{
private:
	EntityID m_IDEventDispatcher;
public:
	AccelerateBallEvent(EntityID _id) : m_IDEventDispatcher(_id) {};

	EntityID GetEventComponent() const { return m_IDEventDispatcher; };
};

class DecelerateBallEvent : public Event
{
private:
	EntityID m_IDEventDispatcher;
public:
	DecelerateBallEvent(EntityID _id) : m_IDEventDispatcher(_id) {};

	EntityID GetEventComponent() const { return m_IDEventDispatcher; };
};

class BrickDestroyedEvent : public Event
{
private:
	unsigned int m_brickID;
	glm::vec2& m_position;

public:
	BrickDestroyedEvent(EntityID _id, glm::vec2& _position) : m_brickID(_id), m_position(_position) {};

	unsigned int GetBrickID() const {return m_brickID;};
	glm::vec2& GetBrickPosition() const {return m_position;};
};

class NoMoreBricksEvent : public Event
{

public:
	NoMoreBricksEvent() {};
};

class CreateMainMenuEvent : public Event
{
public:
	CreateMainMenuEvent() {};
};

class CreateMainLevelEvent : public Event
{
public:
	CreateMainLevelEvent() {};
};

class LoadWinLevelEvent : public Event
{

public:
	LoadWinLevelEvent() {};
};

class LoadDeathLevelEvent : public Event
{

public:
	LoadDeathLevelEvent() {};
};


