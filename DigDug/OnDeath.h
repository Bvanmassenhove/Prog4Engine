#pragma once
#include "Observer.h"
#include "UIComponent.h"
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
			auto HealthComp = gameObject->GetComponent<UIComponent>();
			switch (event)
			{
			case PlayerDied:
				
				HealthComp->UpdateHealth(-1);
				if (HealthComp->GetHealth() <= 0)
				{
					//trigger game over
				}
				break;
			case PookaDied:
				HealthComp->UpdateScore(+200);
				break;
			case FlygarDied:
				HealthComp->UpdateScore(+400);
				break;
			default:
				break;
			}
		}		
	};
}
