#include "FPSComponent.h"
#include "TextComponent.h"
#include <chrono>
#include <string>

using namespace dae;

FPSComponent::FPSComponent(GameObject* object)
	:BaseComponent(object)
{}
void FPSComponent::Update(float deltatime)
{
	m_FrameCount++;
	m_ElapsedTime += deltatime;
	if (m_ElapsedTime > 1.f)
	{
		m_FPS = m_FrameCount;
		m_FrameCount = 0;
		m_ElapsedTime = 0.f;
	}
	const GameObject* owner = BaseComponent::GetOwner();
	owner->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS));
}
void FPSComponent::Render() const {}