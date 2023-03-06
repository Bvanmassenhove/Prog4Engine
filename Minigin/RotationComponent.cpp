#include <stdexcept>
#include <SDL_ttf.h>

#include "RotationComponent.h"

using namespace dae;

RotationComponent::RotationComponent(glm::vec3 rotCenter, float rotSpeed, bool cloackwise, float rotDistance, GameObject* object)
	:m_RotCenter(rotCenter),m_RotSpeed(rotSpeed), m_RotClockwise(cloackwise),m_RotDistance(rotDistance), BaseComponent(object)
{ }


void RotationComponent::Update(float)
{
	/*float s = sin(angle);
	float c = cos(angle);

	float xnew = m_RotCenter.x * c + m_RotCenter.y * s;
	float ynew = -m_RotCenter.x * s + m_RotCenter.y * c;*/
	//rotation is making my head spin
	GameObject* owner = BaseComponent::GetOwner();
	glm::vec3 pos = owner->GetLocalPos();
	if (m_RotClockwise)
	{
		owner->SetLocalPos(glm::vec3{ pos.x + 1.f, pos.y, pos.z });
	}
	else
	{
		owner->SetLocalPos(glm::vec3{ pos.x, pos.y + 1.f, pos.z });
	}
	owner->UpdateWorldPos();
}

void RotationComponent::Render() const {};