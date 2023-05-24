#pragma once
#include "Observer.h"


namespace dae
{
	class  Achievement :public Observer
	{
	public:
		Achievement() {};
		Achievement(const Achievement& other) = delete;
		Achievement(Achievement&& other) = delete;
		Achievement& operator=(const Achievement& other) = delete;
		Achievement& operator=(Achievement&& other) = delete;

		void Notify(Event event, GameObject* gameObject)
		{
			switch (event)
			{
			case ACHWinGame:

				if(gameObject->GetComponent<HealthComponent>() != nullptr)
				{
					if (gameObject->GetComponent<HealthComponent>()->GetScore() >= 50 && ACH_WIN_ONE_GAME == false)
					{
						//SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
						ACH_WIN_ONE_GAME = true;
					}
				}
				break;
			default:
				break;
			}
		}

	private:
		//achievements got:
		bool ACH_WIN_ONE_GAME{ false };
	};
}
