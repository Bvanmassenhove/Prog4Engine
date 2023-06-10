#pragma once
#include "GameObject.h"
#include "Texture2D.h"
#include "CollisionManager.h"

enum Direction
{
	right,
	down,
	left,
	up,
};

namespace dae
{
	class ShootComponent final : public BaseComponent
	{
	public:
		ShootComponent(GameObject* object, std::string& arrowRightFilePath, std::string& arrowLeftFilePath, std::string& arrowUpFilePath, std::string& arrowDownFilePath,float with, float maxLenght, float shotSpeedMulti, float offset);
		virtual ~ShootComponent() = default;
		ShootComponent(const ShootComponent& other) = delete;
		ShootComponent(ShootComponent&& other) = delete;
		ShootComponent& operator=(const ShootComponent& other) = delete;
		ShootComponent& operator=(ShootComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;

		void SetDirection(Direction direction) { m_Direction = direction; }
		Direction GetDirection() { return  m_Direction; }

		void Shoot() { m_Shooting = true;}
		bool GetShooting() { return m_Shooting; }
		GameObject* GetHit() { return m_Hit; }
		void Reset();

	private:
		std::vector<std::shared_ptr<dae::Texture2D>> m_Arrows;
		Direction m_Direction{ right };
		float m_PosX{ 0 };
		float m_PosY{ 0 };
		float m_Lenght{ 0.f };
		float m_MaxLenght{ 128.f };
		float m_With{ 8.f };
		float m_Offset{};
		bool m_Shooting{};
		GameObject* m_Hit{};
		float m_ShootSpeedMulti{};
		CollisionComponent* m_pCollisionComponent;
	};
}
