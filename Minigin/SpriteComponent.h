#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include "GameObject.h"
#include "Texture2D.h"

namespace dae
{
	enum Animation
	{
		moveRight = 0,
		moveDown = 1,
		moveLeft = 2,
		moveUp = 3,
	};

	struct Sprite
	{
		std::shared_ptr<dae::Texture2D> texture;
		int frames;
		int cols;
		float frameTime;
		int currentFrame;
		float accumulatedTime;
		std::pair<float, float> spriteSize;
	};
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(GameObject* object, std::shared_ptr<Sprite> sprite);
		~SpriteComponent();
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update(float) override;
		void Render() const override;

		void AddSprite(std::shared_ptr<Sprite> sprite);
		void SetTransform(float x, float y, float z);
		void SetCurrentAnimation(Animation animation) { m_CurrentAnimation = animation; }

	private:
		//std::vector<Sprite*> m_Sprites;
		std::vector<std::shared_ptr<Sprite>> m_Sprites;
		int m_DrawnSpriteID{0};
		Transform m_Transform{};
		Animation m_CurrentAnimation{ Animation::moveRight };
	};
}
