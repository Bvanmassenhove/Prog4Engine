#pragma once
#include "GameObject.h"
#include "Texture2D.h"

namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent(GameObject* object,int startinghealth, std::string& HealthSpritefilename , float XOffset);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;
		void UpdateHealth(int healthchange);
		void UpdateScore(int ScoreChange);
		int GetStartingHealth() { return m_Health; }
		int GetHealth() { return m_Health; }
		int GetScore() { return m_Score; }
	private:
		std::shared_ptr<dae::Texture2D> m_HealthTexture = nullptr;
		float m_XOffset;
		int m_StartingHealth = 0;
		int m_Health = 0;
		int m_Score = 0;
	};
}
