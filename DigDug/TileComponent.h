#pragma once
#include "GameObject.h"
#include "CollisionManager.h"


namespace dae
{
	class TileComponent final : public BaseComponent
	{
	public:
		TileComponent(GameObject* object, std::string& Tilefilename);
		virtual ~TileComponent() = default;
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;
	private:
		std::shared_ptr<dae::Texture2D> m_TileTexture = nullptr;
		bool m_Render = true;
		CollisionComponent* m_pCollisionComponent;
		float m_X;
		float m_Y;
	};
}