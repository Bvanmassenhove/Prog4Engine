#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "SpriteComponent.h"
#include "Command.h"
#include "GameEvents.h"
#include "Sounds.h"
#include "ServiceLocator.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "LevelSelecter.h"

namespace dae
{
	enum MoveDirection
	{
		MoveUp,
		MoveDown,
		MoveLeft,
		MoveRight
	};

	class ChangeScene : public Command
	{
	public:
		ChangeScene(GameObject* gameObject,int toLoadScene)
			: pGameObject(gameObject),
			toLoadScene(toLoadScene)
		{};
		void Execute(float) override
		{
			auto& sceneManager = SceneManager::GetInstance();
			auto& loadedScene = sceneManager.LoadScene(toLoadScene);

			auto& levelSelector = LevelSelecter::GetInstance();

			switch (toLoadScene)
			{
			case 0:

				levelSelector.LoadMainMenu(loadedScene);
				break;
			case 1:

				levelSelector.LoadSingePlayer(1, loadedScene);
				break;
			case 2:

				levelSelector.LoadCoop(4, loadedScene);
				break;
			case 3:

				levelSelector.LoadPVP(5, loadedScene);
				break;
			default:
				break;
			}
		};
	private:
		GameObject* pGameObject;
		int toLoadScene = 0;
	};

	class ChangeLevel : public Command
	{
	public:
		ChangeLevel(GameObject* gameObject)
			: pGameObject(gameObject)
		{};
		void Execute(float) override
		{
			// increment current level (get the curent loaded level and do ++)
			// have the number of levels in the scene via the scene maneger
			// if current scene == nrOfLevels load main menu

			auto& sceneManager = SceneManager::GetInstance();
			int SceneID = sceneManager.GetSceneID();
			auto& loadedScene = sceneManager.LoadScene(SceneID);

			auto& levelSelector = LevelSelecter::GetInstance();
			int loadedID =  levelSelector.GetLoadedLevel();

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

			
		};
	private:
		GameObject* pGameObject;
		int toLoadLevel = 0;
	};

	class Move : public Command
	{
	public:
		Move(GameObject* gameObject, MoveDirection moveDirection, float moveSpeed)
			: pGameObject(gameObject),
			moveDirection(moveDirection),
			moveSpeed(moveSpeed)
		{};
		void Execute(float deltaTime) override
		{
			glm::vec3 pos = pGameObject->GetLocalPos();
			switch (moveDirection)
			{
			case MoveUp:
				pGameObject->SetLocalPos(glm::vec3{ pos.x, pos.y - moveSpeed * deltaTime, pos.z });
				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveUp);
				}
				break;
			case MoveDown:
				pGameObject->SetLocalPos(glm::vec3{ pos.x, pos.y + moveSpeed * deltaTime, pos.z });
				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveDown);
				}
				break;
			case MoveLeft:
				pGameObject->SetLocalPos(glm::vec3{ pos.x - moveSpeed * deltaTime, pos.y, pos.z });

				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveLeft);
				}
				break;
			case MoveRight:
				pGameObject->SetLocalPos(glm::vec3{ pos.x + moveSpeed * deltaTime, pos.y, pos.z });
				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveRight);
				}
				break;
			default:
				break;
			}
		};
	private:
		GameObject* pGameObject;
		MoveDirection moveDirection;
		float moveSpeed;
	};

	class ChangeHUD : public Command
	{
	public:
		ChangeHUD(GameObject* gameObject,bool playerdied)
			: pGameObject(gameObject),
			playerDied(playerdied)
		{};
		void Execute(float) override
		{
			
			if (playerDied)
			{
				pGameObject->NotifyObservers(Event::PlayerDied);
			}
			else
			{
				pGameObject->NotifyObservers(Event::EnemyDied);
				pGameObject->NotifyObservers(Event::ACHWinGame);
			}
			
		};
	private:
		GameObject* pGameObject;
		bool playerDied; //false to say enemy died to update score
	};

	class Shoot : public Command
	{
	public:
		Shoot(GameObject* gameObject)
			: pGameObject(gameObject)
		{};
		void Execute(float) override
		{
			auto& soundManager = ServiceLocator::Get_Sound_System();
			soundManager.PlaySound(DigDugShoot, 2);
		};
	private:
		GameObject* pGameObject;
	};
}