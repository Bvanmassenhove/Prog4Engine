#pragma once
#include "MovementComponent.h"

namespace dae
{
	class Command
	{
	protected:
		MovementComponent* GetMovementComponent() const { return movementComponent; }
	public:
		explicit Command(MovementComponent* moveComponent): movementComponent(moveComponent){};
		virtual ~Command() = default;
		virtual void Execute() = 0;
	private:
		MovementComponent* movementComponent;
	};

	class MoveUp : public Command
	{
	public:
		MoveUp(MovementComponent* moveComponent): Command(moveComponent) {};
		void Execute() override { GetMovementComponent()->MoveUp(); };
	};
	class MoveLeft : public Command
	{
	public:
		MoveLeft(MovementComponent* moveComponent) : Command(moveComponent) {};
		void Execute() override { GetMovementComponent()->MoveLeft(); };
	};
	class MoveRight : public Command
	{
	public:
		MoveRight(MovementComponent* moveComponent) : Command(moveComponent) {};
		void Execute() override { GetMovementComponent()->MoveRight(); };
	};
	class MoveDown : public Command
	{
	public:
		MoveDown(MovementComponent* moveComponent) : Command(moveComponent) {};
		void Execute() override { GetMovementComponent()->MoveDown(); };
	};

}