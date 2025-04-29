#include "CollisionSystem.h"
#include "../Engine/Engine.h"
#include "EventManager.h"

#include <utility>
#include <iostream>

std::shared_ptr<CollisionSystem> CollisionSystem::m_instance = nullptr;

//Collision system to check collisions in the game
CollisionSystem::CollisionSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager)
{}

//Sinhgleton instance of the CollisionSystem
std::shared_ptr<CollisionSystem> CollisionSystem::GetInstance()
{
	//If doesn't exist an instance of the CollisionSystem return a new one
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<CollisionSystem>(new CollisionSystem());
	}

	return m_instance;
}

void CollisionSystem::Tick(double _deltaTime)
{
	//Iterate through all the colliders of the component manager
	for (std::pair<const EntityID, std::shared_ptr<Collider>>& pair : m_componentManager->GetCollidersComponents())
	{
		//Get the ID from the first element of the unordered map pair
		EntityID id = pair.first;
		if (m_componentManager->GetComponent<RigidBody>(id).GetActive() == true)
		{
			TransformComponent& transformComponent = m_componentManager->GetComponent<TransformComponent>(id);
			RigidBody& rbComponent = m_componentManager->GetComponent<RigidBody>(id);

			//Check only the collisions between the player and the active powerups
			if (m_componentManager->HasComponent<PlayerComponent>(id) == true)
			{
				std::shared_ptr<BoxCollider> colliderComponent = m_componentManager->GetComponentPointer<BoxCollider>(id);
				for (std::pair<const EntityID, std::shared_ptr<PowerUpComponent>>& other : m_componentManager->GetPowerUpsComponents())
				{
					EntityID otherID = other.first;

					if (m_componentManager->GetComponentPointer<PowerUpComponent>(otherID)->GetActive() == true)
					{
						TransformComponent& otherTransformComponent = m_componentManager->GetComponent<TransformComponent>(otherID);
						std::shared_ptr<CircleCollider> othercColliderComponent = m_componentManager->GetComponentPointer<CircleCollider>(otherID);

						//To optimize collision system, only check collision when player is close to powerups
						float distance = glm::length(otherTransformComponent.GetPosition() - transformComponent.GetPosition());
						if (distance > 50)
						{
							continue;
						}

						if (CheckCircleBoxCollision(transformComponent, othercColliderComponent, otherTransformComponent, colliderComponent) == true)
						{
							//Send a specific message depending on the type of power collected
							if (std::dynamic_pointer_cast<AddBallPowerUpComponent>(m_componentManager->GetComponentPointer<PowerUpComponent>(otherID)) != nullptr)
							{
								EventManager::GetInstance().SendMessage(AddNewBallEvent(otherID));
							}

							else if (std::dynamic_pointer_cast<AccelerateBallPowerUp>(m_componentManager->GetComponentPointer<PowerUpComponent>(otherID)) != nullptr)
							{
								EventManager::GetInstance().SendMessage(AccelerateBallEvent(otherID));
							}

							else if (std::dynamic_pointer_cast<DecelerateBallPowerUp>(m_componentManager->GetComponentPointer<PowerUpComponent>(otherID)) != nullptr)
							{
								EventManager::GetInstance().SendMessage(DecelerateBallEvent(otherID));
							}
							
						}
					}
				}
			}

			//If the entity is a powerup or a brick skip the collision detection
			else if (m_componentManager->HasComponent<PowerUpComponent>(id) == true || m_componentManager->HasComponent<BrickComponent>(id) == true)
			{
				continue;
			}

			//The collision component belongs to the ball
			else
			{
				std::shared_ptr<CircleCollider> colliderComponent = m_componentManager->GetComponentPointer<CircleCollider>(id);

				//Check the collisions with the bricks
				for (std::pair<const EntityID, BrickComponent>& other : m_componentManager->GetBrickComponents())
				{
					EntityID otherID = other.first;

					TransformComponent& otherTransformComponent = m_componentManager->GetComponent<TransformComponent>(otherID);
					std::shared_ptr<BoxCollider> otherColliderComponent = m_componentManager->GetComponentPointer<BoxCollider>(otherID);

					//To optimize collision system, only check collision when ball is close to bricks
					float distance = glm::length(otherTransformComponent.GetPosition() - transformComponent.GetPosition());
					if (distance > 50)
					{
						continue;
					}

					if (colliderComponent != nullptr && otherColliderComponent != nullptr && otherColliderComponent->GetActive() == true)
					{

						if (CheckCircleBoxCollision(otherTransformComponent, colliderComponent, transformComponent, otherColliderComponent) == true)
						{
							//Collision algorith to detect the position of the ball from the brick
							//Get all the sides of the ball
							float ballLeft = transformComponent.GetPosition().x - colliderComponent->GetSize() / 2;
							float ballRight = transformComponent.GetPosition().x + colliderComponent->GetSize() / 2;
							float ballTop = transformComponent.GetPosition().y + colliderComponent->GetSize() / 2;
							float ballBottom = transformComponent.GetPosition().y - colliderComponent->GetSize() / 2;

							//Get all the sides of the brick
							float blockLeft = otherTransformComponent.GetPosition().x - otherColliderComponent->GetSize().x / 2;
							float blockRight = otherTransformComponent.GetPosition().x + otherColliderComponent->GetSize().x / 2;
							float blockTop = otherTransformComponent.GetPosition().y + otherColliderComponent->GetSize().y / 2;
							float blockBottom = otherTransformComponent.GetPosition().y - otherColliderComponent->GetSize().y / 2;

							//Check if the ball is overlaping with the brick
							float overlapLeft = ballRight - blockLeft;
							float overlapRight = blockRight - ballLeft;
							float overlapTop = ballBottom - blockTop;
							float overlapBottom = blockBottom - ballTop;

							//Check if the ball is coming from an specific direction
							bool ballFromLeft = overlapLeft < overlapRight;
							bool ballFromTop = overlapTop < overlapBottom;

							float minOverlapX;
							float minOverlapY;

							if (ballFromLeft == true)
							{
								minOverlapX = overlapLeft;
							}

							else
							{
								minOverlapX = overlapRight;
							}


							if (ballFromTop == true)
							{
								minOverlapY = overlapTop;
							}

							else
							{
								minOverlapY = overlapBottom;

							}

							if (minOverlapX < minOverlapY) {
								//Lateral collison
								rbComponent.SetVelocity(glm::vec2(rbComponent.GetVelocity().x * -1.0f, rbComponent.GetVelocity().y));
							}
							else {
								//Vertical collision
								rbComponent.SetVelocity(glm::vec2(rbComponent.GetVelocity().x, rbComponent.GetVelocity().y * -1.0f));
							}

							//Send a BrickDestroyedEvent message
							EventManager::GetInstance().SendMessage(BrickDestroyedEvent(otherID, otherTransformComponent.GetPosition()));
						}
					}
				}

				//Check the collisions with the player
				for (std::pair<const EntityID, PlayerComponent>& other : m_componentManager->GetPlayerComponents())
				{
					EntityID otherID = other.first;

					TransformComponent& otherTransformComponent = m_componentManager->GetComponent<TransformComponent>(otherID);
					std::shared_ptr<BoxCollider> otherColliderComponent = m_componentManager->GetComponentPointer<BoxCollider>(otherID);

					//To optimize collision system, only check collision when ball is close to bricks
					float distance = glm::length(otherTransformComponent.GetPosition() - transformComponent.GetPosition());
					if (distance > 50)
					{
						continue;
					}

					if (CheckCircleBoxCollision(otherTransformComponent, colliderComponent, transformComponent, otherColliderComponent) == true && rbComponent.GetVelocity().y < 0)
					{
						//Modify the velocity of the ball
						glm::vec2 newDirNorm = glm::normalize(otherTransformComponent.GetPosition() - transformComponent.GetPosition());
						rbComponent.SetVelocity(newDirNorm * -glm::length(rbComponent.GetVelocity()));
					}
				}


				//Check collisions of the ball with the borders of the screen
				if (transformComponent.GetPosition().x - colliderComponent->GetSize() < 0)
				{
					glm::vec2 velNormalized = glm::normalize(rbComponent.GetVelocity());

					//get the dot product of the velocity and the screen border to check if the ball is going against the border
					if (glm::dot(velNormalized, glm::vec2(1, 0)) < 1)
					{
						rbComponent.SetVelocity(glm::vec2(rbComponent.GetVelocity().x * -1.0f, rbComponent.GetVelocity().y));
					}
				}

				else if (transformComponent.GetPosition().x + colliderComponent->GetSize() > Engine::GetInstance()->GetWindowData()->GetWindowWidth())
				{
					glm::vec2 velNormalized = glm::normalize(rbComponent.GetVelocity());

					//get the dot product of the velocity and the screen border to check if the ball is going against the border
					if (glm::dot(velNormalized, glm::vec2(-1, 0)) < 1)
					{
						rbComponent.SetVelocity(glm::vec2(rbComponent.GetVelocity().x * -1.0f, rbComponent.GetVelocity().y));
					}
				}

				else if (transformComponent.GetPosition().y + colliderComponent->GetSize() > Engine::GetInstance()->GetWindowData()->GetWindowHeight() - 100)
				{
					glm::vec2 velNormalized = glm::normalize(rbComponent.GetVelocity());

					//get the dot product of the velocity and the screen border to check if the ball is going against the border
					if (glm::dot(velNormalized, glm::vec2(0, -1)) < 1)
					{
						rbComponent.SetVelocity(glm::vec2(rbComponent.GetVelocity().x, rbComponent.GetVelocity().y * -1.0f));
					}
				}
			}
		}
	}
}

bool CollisionSystem::CheckCircleBoxCollision(TransformComponent& _boxTransformComponent, std::shared_ptr<CircleCollider>& colliderComponent, TransformComponent& _circleTransformComponent, std::shared_ptr<BoxCollider>& _boxColliderComponent)
{
	//To check the collision between circle and box colliders get the nearest point of the box regarding with the circle
	float closestCirclePointX = std::max(_boxTransformComponent.GetPosition().x - _boxColliderComponent->GetSize().x / 2, std::min(_circleTransformComponent.GetPosition().x, _boxTransformComponent.GetPosition().x - _boxColliderComponent->GetSize().x / 2
		+ _boxColliderComponent->GetSize().x));
	float closestCirclePointY = std::max(_boxTransformComponent.GetPosition().y, std::min(_circleTransformComponent.GetPosition().y, _boxTransformComponent.GetPosition().y + _boxColliderComponent->GetSize().y));
	glm::vec2 closestCirclePoint(closestCirclePointX, closestCirclePointY);

	//Get the distance between the circle and  the nearest point
	glm::vec2 distance = _circleTransformComponent.GetPosition() - closestCirclePoint;

	//Squared distance
	float distanceSquared = (distance.x * distance.x) + (distance.y * distance.y);

	//Check if exists a collision between the circle and the box colliders
	if (distanceSquared <= (colliderComponent->GetSize() * colliderComponent->GetSize()))
	{
		return true;
	}

	return false;
}
