#pragma once
#include "GameObject.h"
#include "CollisionManager.h"

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(GameObject* object, glm::vec3 spawn);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;

		
	private:
		CollisionComponent* m_pCollisionComponent;
		glm::vec3 m_Spawn;
	};
}