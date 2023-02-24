#pragma once
#include "baseComponent.h"

class FPSComponent final : public baseComponent
{
public:

	FPSComponent() = default;
	virtual ~FPSComponent() = default;

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	void update(float deltatime);
	int GetFPS() { return m_FPS; }
private:
	int m_FPS = 0;
	int m_FrameCount = 0;
	float m_ElapsedTime = 0.f;
};