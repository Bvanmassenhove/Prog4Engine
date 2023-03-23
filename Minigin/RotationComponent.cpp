#include <stdexcept>
#include <SDL_ttf.h>

#include "RotationComponent.h"

using namespace dae;

RotationComponent::RotationComponent(float angle, float rotDistance, bool cloackwise, GameObject* object)
	:m_Angle(angle), m_RotDistance(rotDistance), m_RotClockwise(cloackwise), BaseComponent(object)
{ }


void RotationComponent::Update(float)
{

	//float x = m_RotDistance * cos(m_RotSpeed)
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