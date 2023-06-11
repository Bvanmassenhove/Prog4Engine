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

			loadedScene.PauseUpdate( false);

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
		Move(GameObject* gameObject, MoveDirection moveDirection, float moveSpeed, int movePixel)
			: pGameObject(gameObject),
			moveDirection(moveDirection),
			moveSpeed(moveSpeed),
			movePixels(movePixel)
		{};
		void Execute(float deltaTime) override
		{
			glm::vec3 pos = pGameObject->GetLocalPos();
			if(pGameObject->GetComponent<ShootComponent>()->GetShooting() || pGameObject->GetComponent<ShootComponent>()->GetHit())
			{
				return;
			}

			auto spriteComponent = pGameObject->GetComponent<SpriteComponent>();
			auto shootComponent = pGameObject->GetComponent<ShootComponent>();

			switch (moveDirection)
			{
			case MoveUp:

				movementY -= moveSpeed * deltaTime;
				
				if (movementY <= -movePixels)
				{
					pGameObject->SetLocalPos(glm::vec3{ pos.x, pos.y - movePixels, pos.z });
					movementX = 0.f;
					movementY = 0.f;


					if (spriteComponent != nullptr)
					{
						spriteComponent->SetCurrentAnimation(Animation::moveUp);

					}
					if (shootComponent != nullptr)
					{
						shootComponent->SetDirection(up);
					}
				}
				break;
			case MoveDown:
				movementY += moveSpeed * deltaTime;
				if (movementY >= movePixels)
				{
					pGameObject->SetLocalPos(glm::vec3{ pos.x, pos.y + movePixels, pos.z });
					movementX = 0.f;
					movementY = 0.f;


					if (spriteComponent != nullptr)
					{
						spriteComponent->SetCurrentAnimation(Animation::moveDown);
					}
					if (shootComponent != nullptr)
					{
						shootComponent->SetDirection(down);
					}
				}
				
				break;
			case MoveLeft:

				movementX -= moveSpeed * deltaTime;
				if (movementX <= -movePixels)
				{
					pGameObject->SetLocalPos(glm::vec3{ pos.x - movePixels, pos.y, pos.z });
					movementX = 0.f;
					movementY = 0.f;


					if (spriteComponent != nullptr)
					{
						spriteComponent->SetCurrentAnimation(Animation::moveLeft);
					}
					if (shootComponent != nullptr)
					{
						shootComponent->SetDirection(left);
					}
				}
				
				break;
			case MoveRight:
				movementX += moveSpeed * deltaTime;
				if (movementX >= movePixels)
				{
					pGameObject->SetLocalPos(glm::vec3{ pos.x + movePixels, pos.y, pos.z });
					movementX = 0.f;
					movementY = 0.f;


					if (spriteComponent != nullptr)
					{
						spriteComponent->SetCurrentAnimation(Animation::moveRight);
					}
					if (shootComponent != nullptr)
					{
						shootComponent->SetDirection(right);
					}
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
		int movePixels;

		float movementX{ 0 };
		float movementY{ 0 };

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
				pGameObject->NotifyObservers(Event::PookaDied);
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
			auto shootcomponent = pGameObject->GetComponent<ShootComponent>();
			if (shootcomponent != nullptr && shootcomponent->GetHit() != nullptr)
			{	
				auto& soundManager = ServiceLocator::Get_Sound_System();
				soundManager.PlaySound(Pump, 2);
				if(NrPumps == 3)
				{
					if (shootcomponent->GetHit()->GetComponent<CollisionComponent>(1)->GetCollisionFlag() == Pooka)
					{
						pGameObject->NotifyObservers(Event::PookaDied);
					}
					else if (shootcomponent->GetHit()->GetComponent<CollisionComponent>(1)->GetCollisionFlag() == Flygar)
					{
						pGameObject->NotifyObservers(Event::FlygarDied);
					}
					auto& sceneManager = SceneManager::GetInstance();
					int SceneID = sceneManager.GetSceneID();
					auto& loadedScene = sceneManager.LoadScene(SceneID);
					loadedScene.Remove(shootcomponent->GetHit());
					shootcomponent->Reset();
					
					NrPumps = 0;
				}
				else
				{
					shootcomponent->GetHit()->GetComponent<SpriteComponent>()->NextFrame();
					NrPumps++;
				}
			}
			else
			{
				auto& soundManager = ServiceLocator::Get_Sound_System();
				soundManager.PlaySound(DigDugShoot, 2);
				if (shootcomponent != nullptr)
				{
					shootcomponent->Shoot();
				}
			}
		};
	private:
		GameObject* pGameObject;
		int NrPumps{ 0 };
	};
}