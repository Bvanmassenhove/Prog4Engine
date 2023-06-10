#include "PookaComponent.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include <iostream>

using namespace dae;

 PookaComponent:: PookaComponent(GameObject* object)
	:BaseComponent(object)
{
	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>(1);
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << " PookaComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
	/*for (int i = 1; i < 5; i++)
	{
		auto comp = GetOwner()->GetComponent<CollisionComponent>(i);
		if (comp == nullptr)
		{
			std::cout << " PookaComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
		}
		m_pAICollisions.emplace_back(comp);
	}*/

}
void  PookaComponent::Update(float/* deltaTime*/)
{
	int sceneId = SceneManager::GetInstance().GetSceneID();


	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if (collisionComponent->GetCollisionFlag() == Arrow && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()) || collisionComponent->GetCollisionFlag() == Flame && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			GetOwner()->GetComponent<SpriteComponent>()->SetCurrentAnimation(dying);
		}

		/*if (m_pAICollisions.size() == 4)
		{
			if (m_MoveDirection == Pookaleft || m_MoveDirection == Pookaright)
			{
				m_MoveSwitch = 0;
				if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pAICollisions[2]->GetCollisionRect()))
				{
					m_MoveDirection = Pookaright;
					m_MoveSwitch++;
				}
				if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pAICollisions[3]->GetCollisionRect()))
				{
					m_MoveDirection = Pookaleft;
					m_MoveSwitch++;
				}
			}
			if (m_MoveSwitch == 2)
			{
				if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pAICollisions[0]->GetCollisionRect()))
				{
					m_MoveDirection = Pookadown;
				}
				else if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pAICollisions[1]->GetCollisionRect()))
				{
					m_MoveDirection = Pookaup;
				}
			}
		}*/
	}
	
	/*if (m_MoveDirection == Pookaleft)
	{
		glm::vec3 pos = GetOwner()->GetLocalPos();
		GetOwner()->SetLocalPos(glm::vec3{ pos.x -= 30.f * deltaTime, pos.y, pos.z });
	}
	else if (m_MoveDirection == Pookaright)
	{
		glm::vec3 pos = GetOwner()->GetLocalPos();
		GetOwner()->SetLocalPos(glm::vec3{ pos.x += 30.f * deltaTime, pos.y, pos.z });
	}
	else if (m_MoveDirection == Pookaup)
	{
		glm::vec3 pos = GetOwner()->GetLocalPos();
		GetOwner()->SetLocalPos(glm::vec3{ pos.x, pos.y -= 30.f * deltaTime, pos.z });
	}
	else if (m_MoveDirection == Pookadown)
	{
		glm::vec3 pos = GetOwner()->GetLocalPos();
		GetOwner()->SetLocalPos(glm::vec3{ pos.x, pos.y += 30.f * deltaTime, pos.z });
	}*/

}
void  PookaComponent::Render() const {}
