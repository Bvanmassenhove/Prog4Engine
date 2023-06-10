#include "UIComponent.h"
#include "TextComponent.h"
#include <sstream>
#include "ResourceManager.h"
#include "Renderer.h"


using namespace dae;

UIComponent::UIComponent(GameObject* object, int startinghealth, int startingScore, std::string& HealthSpritefilename, float XOffset)
	:BaseComponent(object),
	m_StartingHealth(startinghealth),
	m_Health(startinghealth),
	m_Score(startingScore),
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

	m_UIss.str(std::string());
	m_UIss <<  " Score: " << m_Score;

	owner->GetComponent<TextComponent>(1)->SetText(m_UIss.str());

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

void UIComponent::GameEnd() 
{
	m_GameOverSS << "GAME OVER: SCORE: " << m_Score;
	GetOwner()->GetComponent<TextComponent>(2)->SetText(m_GameOverSS.str());
	m_RestartSS << "Press START to return";
	GetOwner()->GetComponent<TextComponent>(3)->SetText(m_RestartSS.str());
	//bad code but it works. if i have time it will be fixed
	GetOwner()->GetComponent<TextComponent>(2)->Update(0.f);
	GetOwner()->GetComponent<TextComponent>(3)->Update(0.f);
}

