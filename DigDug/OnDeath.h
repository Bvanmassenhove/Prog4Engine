#pragma once
#include "Observer.h"
#include "UIComponent.h"
#include "GameModeComponent.h"
#include "GameEvents.h"

namespace dae
{
	class  OnDeath :public Observer
	{
	public:
		OnDeath() {};
		OnDeath(const OnDeath& other) = delete;
		OnDeath(OnDeath&& other) = delete;
		OnDeath& operator=(const OnDeath& other) = delete;
		OnDeath& operator=(OnDeath&& other) = delete;

		void Notify(int event, GameObject* gameObject)
		{
			auto UIComp = gameObject->GetComponent<UIComponent>();
			auto& sceneManager = SceneManager::GetInstance();
			int SceneID = sceneManager.GetSceneID();
			auto& loadedScene = sceneManager.LoadScene(SceneID);
			switch (event)
			{
			case PlayerDied:
				
				UIComp->UpdateHealth(-1);
				if (UIComp->GetHealth() <= 0)
				{
					loadedScene.GetGameMode()->GetComponent<GameModeComponent>()->SaveScoreToFile();
					UIComp->GameEnd();
					loadedScene.PauseUpdate(true);
				}
				break;
			case PookaDied:
				loadedScene.GetGameMode()->GetComponent<GameModeComponent>()->UpdateScore(+200);
				UIComp->UpdateScore(+200);
				loadedScene.RemoveEnemy();
				break;
			case FlygarDied:
				loadedScene.GetGameMode()->GetComponent<GameModeComponent>()->UpdateScore(+400);
				UIComp->UpdateScore(+400);
				loadedScene.RemoveEnemy();
				break;
			default:
				break;
			}
			
		}		
	};
}
