#pragma once
#include <string>
#include <memory>
#include "baseComponent.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
	class TextureComponent final : public baseComponent
	{
	public:
		TextureComponent() = default;
		TextureComponent(const std::string& filename);
		~TextureComponent() = default;
		virtual void Render();
		virtual void SetTexture(const std::string& filename);
		virtual void SetTransform(float x, float y, float z);

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_Texture{};
		Transform m_Transform{};
	};
}
