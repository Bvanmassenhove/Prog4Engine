#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"
#include <vector>


namespace dae
{
	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void AddCollisionComponent(CollisionComponent* CollisionComponent , int SceneID);
		std::vector<CollisionComponent*> GetCollisionComponentsFromScene(int SceneID);

	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;

		
		
		std::vector<std::pair<CollisionComponent*,int>> m_CollisionComponents;
	};
}


