#pragma once
#include "GameObject.h"
#include "CollisionManager.h"


namespace dae
{
	class  FlygarComponent final : public BaseComponent
	{
	public:
		FlygarComponent(GameObject* object);
		virtual ~FlygarComponent() = default;
		FlygarComponent(const  FlygarComponent& other) = delete;
		FlygarComponent(FlygarComponent&& other) = delete;
		FlygarComponent& operator=(const  FlygarComponent& other) = delete;
		FlygarComponent& operator=(FlygarComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;


	private:
		CollisionComponent* m_pCollisionComponent;

	};
}