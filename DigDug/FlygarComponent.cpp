#include "FlygarComponent.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include <iostream>

using namespace dae;

FlygarComponent::FlygarComponent(GameObject* object)
	:BaseComponent(object)
{
	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>(1);
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << " FlygarComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
}
void  FlygarComponent::Update(float)
{
	int sceneId = SceneManager::GetInstance().GetSceneID();

	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if (collisionComponent->GetCollisionFlag() == Arrow && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			GetOwner()->GetComponent<SpriteComponent>()->SetCurrentAnimation(dying);
		}
	}
}
void  FlygarComponent::Render() const {}
