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

void CollisionManager::ClearCollisionComponentsFromScene(int SceneID)
{
	m_CollisionComponents.erase(std::remove_if(m_CollisionComponents.begin(), m_CollisionComponents.end(), [SceneID](const std::pair<CollisionComponent*, int>& pair) 
		{
		return pair.second == SceneID;
		}), m_CollisionComponents.end());
}