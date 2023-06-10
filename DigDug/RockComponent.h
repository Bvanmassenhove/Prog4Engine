#pragma once
#include "GameObject.h"
#include "CollisionManager.h"


namespace dae
{
	class RockComponent final : public BaseComponent
	{
	public:
		RockComponent(GameObject* object, std::string& rockfilename);
		virtual ~RockComponent() = default;
		RockComponent(const RockComponent& other) = delete;
		RockComponent(RockComponent&& other) = delete;
		RockComponent& operator=(const RockComponent& other) = delete;
		RockComponent& operator=(RockComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;
	private:
		std::shared_ptr<dae::Texture2D> m_RockTexture = nullptr;
		bool m_Render = true;
		CollisionComponent* m_pCollisionComponent;
		CollisionComponent* m_pCollisionComponentDown;
		float m_X;
		float m_Y;
		bool m_CanFall{ false };
		float m_FallSpeed{ 60.f };
	};
}
