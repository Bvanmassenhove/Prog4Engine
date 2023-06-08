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
}
void  PookaComponent::Update(float)
{
	int sceneId = SceneManager::GetInstance().GetSceneID();

	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if (collisionComponent->GetCollisionFlag() == Arrow && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()) || collisionComponent->GetCollisionFlag() == Flame && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			GetOwner()->GetComponent<SpriteComponent>()->SetCurrentAnimation(dying);
		}
	}
}
void  PookaComponent::Render() const {}
