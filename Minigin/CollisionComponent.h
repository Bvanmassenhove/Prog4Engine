#pragma once
#include "GameObject.h"

namespace dae
{
	struct rectf
	{
		float left;
		float bottom;
		float width;
		float height;
	};

	enum CollisionFlag
	{
		Off,
		Player,
		Pooka,
		Flygar,
		Rock,
		Level,
		Arrow,
		Flame,
		AI
	};

	class CollisionComponent final : public BaseComponent
	{
	public:
		CollisionComponent(GameObject* object, rectf collisionRect , CollisionFlag flag, bool DEBUG, float offsetX = 0.f, float offsetY = 0.f);
		virtual ~CollisionComponent() = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) = delete;

		void Update(float deltatime) override;
		void Render() const override;

		bool IsOverlap(rectf rect2);

		void SetCollisionFlag(CollisionFlag flag) { m_CollisionFlag = flag; }
		CollisionFlag GetCollisionFlag() const { return m_CollisionFlag; }
		rectf GetCollisionRect() const { return m_CollisionRect; }
		void SetCollisionRect(rectf newRect) { m_CollisionRect = newRect; }

		GameObject* GetComponentOwner() { return GetOwner(); }

	private:
		rectf m_CollisionRect;
		CollisionFlag m_CollisionFlag = CollisionFlag::Off;
		bool m_DEBUGON = true;
		float m_OffsetX{ 0 };
		float m_OffsetY{ 0 };
	};
}

