#include "CollisionManager.h"

using namespace dae;
void CollisionManager::AddCollisionComponent(CollisionComponent* CollisionComponent, int SceneID)
{
	m_CollisionComponents.emplace_back(CollisionComponent,SceneID);
}

std::vector<CollisionComponent*> CollisionManager::GetCollisionComponentsFromScene(int SceneID)
{
	std::vector<CollisionComponent*> tempVector;

	for (auto collisionComponent : m_CollisionComponents)
	{
		if (collisionComponent.second == SceneID)
		{
			tempVector.emplace_back(collisionComponent.first);
		}
	}
	return tempVector;
}