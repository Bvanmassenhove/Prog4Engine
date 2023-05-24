#include <stdexcept>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"

using namespace dae;

TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, GameObject* object)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr) , BaseComponent(object)
{
	m_Transform = object->GetWorldPos();
}

TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, GameObject* object, glm::vec3 transform)
	: m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr), BaseComponent(object), m_Transform(transform)
{}

void TextComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_Texture != nullptr)
	{
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_Transform.x, m_Transform.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::SetPosition(const float x, const float y)
{
	m_Transform.x = x;
	m_Transform.y = y;
}

