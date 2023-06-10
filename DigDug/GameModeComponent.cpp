#include "GameModeComponent.h"
#include "LevelSelecter.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include <sstream>

using namespace dae;

GameModeComponent::GameModeComponent(GameObject* object)
	:BaseComponent(object)
{

}
void  GameModeComponent::Update(float)
{
	auto& sceneManager = SceneManager::GetInstance();
	int SceneID = sceneManager.GetSceneID();
	auto& loadedScene = sceneManager.LoadScene(SceneID);
	if (loadedScene.GetRemainingEnemies() == 0)
	{
		auto& levelSelector = LevelSelecter::GetInstance();
		int loadedID = levelSelector.GetLoadedLevel();

		//dumb solution
		if (loadedID == 1 || loadedID == 2)
		{
			levelSelector.SetLoadedLevel(++loadedID);
			levelSelector.LoadSingePlayer(loadedID, loadedScene);
		}
		else if (loadedID == 3 || loadedID == 4 || loadedID == 5)
		{
			// if ending final level in scene reset and go to main menu
			levelSelector.SetLoadedLevel(0);
			sceneManager.LoadScene(0);
		}
	}

	
}
void  GameModeComponent::Render() const {}

void GameModeComponent::UpdateScore(int ScoreChange)
{
	m_Score += ScoreChange;
}


void GameModeComponent::ReadScoreFromFile()
{
	std::ifstream HighScoreFile(ResourceManager::GetInstance().GetDataPath() + "HighScore.txt");
	HighScoreFile >> m_HighScore;
}

void GameModeComponent::SaveScoreToFile()
{
	if (m_Score > m_HighScore)
	{
		std::ofstream HighScoreFile(ResourceManager::GetInstance().GetDataPath() + "HighScore.txt");
		HighScoreFile << m_Score;
		m_HighScore = m_Score;
	}

	std::stringstream highscore;
	highscore.str(std::string());
	highscore << "all time best: " << m_HighScore;
	GetOwner()->GetComponent<TextComponent>()->SetText(highscore.str());
	GetOwner()->GetComponent<TextComponent>()->Update(0.f);
}