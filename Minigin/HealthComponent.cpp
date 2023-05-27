#include "HealthComponent.h"
#include "TextComponent.h"
#include <sstream>
#include "ResourceManager.h"
#include "Renderer.h"


using namespace dae;

HealthComponent::HealthComponent(GameObject* object, int startinghealth, std::string& HealthSpritefilename, float XOffset)
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
void HealthComponent::Update(float) 
{
	const GameObject* owner = BaseComponent::GetOwner();

	std::stringstream ss;
	ss << "Health: " << m_Health << " Score: " << m_Score;

	owner->GetComponent<TextComponent>()->SetText(ss.str());
}
void HealthComponent::Render() const 
{
	if (m_HealthTexture != nullptr)
	{
		for (int i = 0; i < m_Health - 1; i++)
		{
			Renderer::GetInstance().RenderTexture(*m_HealthTexture, m_XOffset + 40.f * i, 0);
		}
	}
}

void HealthComponent::UpdateHealth(int healthchange)
{
	m_Health += healthchange;
}
void HealthComponent::UpdateScore(int ScoreChange)
{
	m_Score += ScoreChange;
}