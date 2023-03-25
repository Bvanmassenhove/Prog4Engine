#include "MovementComponent.h"

using namespace dae;

MovementComponent::MovementComponent(GameObject* object,float movementSpeed)
	:BaseComponent(object),
	m_MoveSpeed(movementSpeed)
{}
void MovementComponent::Update(float) {};
void MovementComponent::Render() const {};

const void MovementComponent::MoveUp()
{
	GameObject* owner = BaseComponent::GetOwner();
	glm::vec3 pos = owner->GetLocalPos();
	owner->SetLocalPos(glm::vec3{ pos.x, pos.y - m_MoveSpeed, pos.z });
}
const void MovementComponent::MoveLeft()
{
	GameObject* owner = BaseComponent::GetOwner();
	glm::vec3 pos = owner->GetLocalPos();
	owner->SetLocalPos(glm::vec3{ pos.x - m_MoveSpeed, pos.y, pos.z });
}
const void MovementComponent::MoveRight()
{
	GameObject* owner = BaseComponent::GetOwner();
	glm::vec3 pos = owner->GetLocalPos();
	owner->SetLocalPos(glm::vec3{ pos.x + m_MoveSpeed, pos.y, pos.z });
}
const void MovementComponent::MoveDown()
{
	GameObject* owner = BaseComponent::GetOwner();
	glm::vec3 pos = owner->GetLocalPos();
	owner->SetLocalPos(glm::vec3{ pos.x, pos.y + m_MoveSpeed, pos.z });
}