#pragma once
#include "GameObject.h"
#include "CollisionManager.h"


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

	};
}