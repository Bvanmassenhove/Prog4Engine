#pragma once
#include "GameObject.h"

namespace dae
{

	class MovementComponent final : public BaseComponent
	{
	public:
		MovementComponent(GameObject* object, float movementSpeed);
		virtual ~MovementComponent() = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;


		void Update(float deltatime) override;
		void Render() const override;
		const void MoveUp();
		const void MoveLeft();
		const void MoveRight();
		const void MoveDown();
	private:
		float m_MoveSpeed;
	};
}