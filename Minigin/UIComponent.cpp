#include "UIComponent.h"
#include "TextComponent.h"
#include <sstream>
#include "ResourceManager.h"
#include "Renderer.h"


using namespace dae;

UIComponent::UIComponent(GameObject* object, int startinghealth, std::string& HealthSpritefilename, float XOffset)
	:BaseComponent(object),
	m_StartingHealth(startinghealth),
	m_Health(startinghealth),
	m_XOffset(XOffset)
{
	if (HealthSpritefilename != "")
	{
		m_HealthTexture = ResourceManager::GetInstance().LoadTexture(HealthSpritefilename);
	}
}
void UIComponent::Update(float) 
{
	const GameObject* owner = BaseComponent::GetOwner();

	std::stringstream ss;
	ss <<  " Score: " << m_Score;

	owner->GetComponent<TextComponent>()->SetText(ss.str());
}
void UIComponent::Render() const 
{
	if (m_HealthTexture != nullptr)
	{
		for (int i = 0; i < m_Health - 1; i++)
		{
			Renderer::GetInstance().RenderTexture(*m_HealthTexture, m_XOffset + 40.f * i, 0);
		}
	}
}

void UIComponent::UpdateHealth(int healthchange)
{
	m_Health += healthchange;
}
void UIComponent::UpdateScore(int ScoreChange)
{
	m_Score += ScoreChange;
}