#include <memory>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font, GameObject* object);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:

		bool m_NeedsUpdate;
		std::string m_Text;
		dae::Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
	};
}