#pragma once
#include "GameObject.h"


namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(GameObject* object);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;
		int GetFPS() { return m_FPS; }
	private:
		int m_FPS = 0;
		int m_FrameCount = 0;
		float m_ElapsedTime = 0.f;
	};
}
