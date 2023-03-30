#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		explicit Command(){};
		virtual ~Command() = default;
		virtual void Execute() = 0;
	private:
	};

	class MoveUpDown : public Command
	{
	public:
		MoveUpDown(GameObject* gameObject, bool moveUp,float moveSpeed)
			: gameObject(gameObject),
			moveUp(moveUp),
			moveSpeed(moveSpeed)
		{};
		void Execute() override 
		{ 
			glm::vec3 pos = gameObject->GetLocalPos();
			if (moveUp)
			{
				gameObject->SetLocalPos(glm::vec3{ pos.x, pos.y - moveSpeed, pos.z });
			}
			else
			{
				gameObject->SetLocalPos(glm::vec3{ pos.x, pos.y + moveSpeed, pos.z });
			}
			
		};
	private:
		GameObject* gameObject;
		bool moveUp;
		float moveSpeed;
	};

	class MoveLeftRight : public Command
	{
	public:
		MoveLeftRight(GameObject* gameObject, bool moveLeft, float moveSpeed)
			: gameObject(gameObject),
			moveLeft(moveLeft),
			moveSpeed(moveSpeed)
		{};
		void Execute() override
		{
			glm::vec3 pos = gameObject->GetLocalPos();
			if (moveLeft)
			{
				gameObject->SetLocalPos(glm::vec3{ pos.x - moveSpeed, pos.y, pos.z });
			}
			else
			{
				gameObject->SetLocalPos(glm::vec3{ pos.x + moveSpeed, pos.y, pos.z });
			}

		};
	private:
		GameObject* gameObject;
		bool moveLeft;
		float moveSpeed;
	};
}