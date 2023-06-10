#pragma once
#include "GameObject.h"
#include "CollisionManager.h"


namespace dae
{
	class  GameModeComponent final : public BaseComponent
	{
	public:
		GameModeComponent(GameObject* object);
		virtual ~GameModeComponent() = default;
		GameModeComponent(const  GameModeComponent& other) = delete;
		GameModeComponent(GameModeComponent&& other) = delete;
		GameModeComponent& operator=(const  GameModeComponent& other) = delete;
		GameModeComponent& operator=(GameModeComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;

		void UpdateScore(int ScoreChange);
		int GetScore() { return m_Score;}

		void ReadScoreFromFile();
		void SaveScoreToFile();

	private:
		int m_Score{};
		int m_HighScore{};
	};
}
