#pragma once
#include "GameObject.h"
#include "Observer.h"
#include "SpriteComponent.h"
#include "Command.h"
#include "GameEvents.h"
#include "Sounds.h"
#include "ServiceLocator.h"
#include "SceneManager.h"

namespace dae
{
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
			sceneManager.LoadScene(toLoadScene);		
		};
	private:
		GameObject* pGameObject;
		int toLoadScene = 0;
	};

	class MoveUpDown : public Command
	{
	public:
		MoveUpDown(GameObject* gameObject, bool moveUp,float moveSpeed)
			: pGameObject(gameObject),
			moveUp(moveUp),
			moveSpeed(moveSpeed)
		{};
		void Execute(float deltaTime) override
		{ 
			glm::vec3 pos = pGameObject->GetLocalPos();
			if (moveUp)
			{
				pGameObject->SetLocalPos(glm::vec3{ pos.x, pos.y - moveSpeed * deltaTime, pos.z });
				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveUp);
				}
			}
			else
			{
				pGameObject->SetLocalPos(glm::vec3{ pos.x, pos.y + moveSpeed * deltaTime, pos.z });
				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveDown);
				}
			}
		};
	private:
		GameObject* pGameObject;
		bool moveUp;
		float moveSpeed;
	};

	class MoveLeftRight : public Command
	{
	public:
		MoveLeftRight(GameObject* gameObject, bool moveLeft, float moveSpeed)
			: pGameObject(gameObject),
			moveLeft(moveLeft),
			moveSpeed(moveSpeed)
		{};
		void Execute(float deltaTime) override
		{
			glm::vec3 pos = pGameObject->GetLocalPos();
			if (moveLeft)
			{
				pGameObject->SetLocalPos(glm::vec3{ pos.x - moveSpeed * deltaTime, pos.y, pos.z });

				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveLeft);
				}
			}
			else
			{
				pGameObject->SetLocalPos(glm::vec3{ pos.x + moveSpeed * deltaTime, pos.y, pos.z });
				if (pGameObject->GetComponent<SpriteComponent>() != nullptr)
				{
					pGameObject->GetComponent<SpriteComponent>()->SetCurrentAnimation(Animation::moveRight);
				}
			}
			
		};
	private:
		GameObject* pGameObject;
		bool moveLeft;
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