#pragma once
#include "GameObject.h"
#include "CollisionManager.h"

enum MoveDir
{
	Pookaup,
	Pookadown,
	Pookaleft,
	Pookaright
};
namespace dae
{
	class  PookaComponent final : public BaseComponent
	{
	public:
		 PookaComponent(GameObject* object);
		virtual ~ PookaComponent() = default;
		 PookaComponent(const  PookaComponent& other) = delete;
		 PookaComponent( PookaComponent&& other) = delete;
		 PookaComponent& operator=(const  PookaComponent& other) = delete;
		 PookaComponent& operator=( PookaComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;


	private:
		CollisionComponent* m_pCollisionComponent;
		std::vector<CollisionComponent*> m_pAICollisions;
		MoveDir m_MoveDirection{ Pookaleft };
		int m_MoveSwitch{0};
	};
}