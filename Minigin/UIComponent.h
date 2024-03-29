#pragma once
#include "GameObject.h"
#include "Texture2D.h"


#include <sstream>

namespace dae
{
	class UIComponent final : public BaseComponent
	{
	public:
		UIComponent(GameObject* object,int startinghealth, int startingScore, std::string& HealthSpritefilename , float XOffset);
		virtual ~UIComponent() = default;
		UIComponent(const UIComponent& other) = delete;
		UIComponent(UIComponent&& other) = delete;
		UIComponent& operator=(const UIComponent& other) = delete;
		UIComponent& operator=(UIComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;
		void UpdateHealth(int healthchange);
		void UpdateScore(int ScoreChange);
		int GetStartingHealth() { return m_Health; }
		int GetHealth() { return m_Health; }
		int GetScore() { return m_Score; }
		void GameEnd();
	private:
		std::shared_ptr<dae::Texture2D> m_HealthTexture = nullptr;
		float m_XOffset;
		int m_StartingHealth = 0;
		int m_Health = 0;
		int m_Score = 0;
		bool m_GameEnd{ false };
		std::stringstream m_UIss;
		std::stringstream m_GameOverSS;
		std::stringstream m_RestartSS;
	};
}
