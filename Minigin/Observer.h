#pragma once
#include "Gameobject.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;

		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;

		virtual void Notify(int event, GameObject* gameObject) = 0;
	protected:
		Observer() {};
	};
}
