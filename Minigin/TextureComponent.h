#pragma once
#include <string>
#include <memory>
#include "BaseComponent.h"
#include "Transform.h"
#include "GameObject.h"

namespace dae
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent(std::string& filename, GameObject* object);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Update(float) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTransform(float x, float y, float z);
	private:
		std::shared_ptr<dae::Texture2D> m_Texture{};
		dae::Transform m_Transform{};
	};
}
