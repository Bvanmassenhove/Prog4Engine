#include "PlayerComponent.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "../DigDug/GameEvents.h"
#include "servicelocator.h"
#include "../DigDug/Sounds.h"
#include <iostream>

using namespace dae;

PlayerComponent::PlayerComponent(GameObject* object, glm::vec3 spawn)
	:BaseComponent(object),
	m_Spawn(spawn)
{
	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>();
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << "PlayerComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
}
void PlayerComponent::Update(float)
{
	int sceneId = SceneManager::GetInstance().GetSceneID();

	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if(collisionComponent->GetCollisionFlag() == Pooka && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			GetOwner()->NotifyObservers(Event::PlayerDied);
			GetOwner()->SetLocalPos(m_Spawn);
			auto& soundManager = ServiceLocator::Get_Sound_System();
			soundManager.PlaySound(HitSound, 2);
		}
		/*if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			std::cout << "hit level";
		}*/
	}
}
void PlayerComponent::Render() const {}