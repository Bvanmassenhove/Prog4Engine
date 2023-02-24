#include "FPSComponent.h"
#include <chrono>

void FPSComponent::update(float deltatime)
{
	m_FrameCount++;
	m_ElapsedTime += deltatime;
	if (m_ElapsedTime > 1.f)
	{
		m_FPS = m_FrameCount;
		m_FrameCount = 0;
		m_ElapsedTime = 0.f;
	}
}