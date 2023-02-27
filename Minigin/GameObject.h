#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update(float deltatime);
		void Render();
		void SetPosition(float x, float y);
		void AddComponent(BaseComponent* component);
		template <typename T> T* GetComponent() const
		{
			for (BaseComponent* component : m_Components)
			{
				if (dynamic_cast<T*>(component))
					return (T*)component;
			}
			return nullptr;
		}
		template <typename T> bool RemoveComponent(T* ToRemoveComponent)
		{

			for (BaseComponent* component : m_Components)
			{
				if (dynamic_cast<T*>(component))
				{
					m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), ToRemoveComponent), m_Components.end());
					return true;
				}
			}
			return false;
		}

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<BaseComponent*> m_Components;
		dae::Transform m_Transform;
	};
}
