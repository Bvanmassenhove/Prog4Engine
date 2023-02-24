#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "baseComponent.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update();

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		void AddComponent(baseComponent* component);
		template <typename T> T* GetComponent() const
		{
			for (baseComponent* component : m_Components)
			{
				if (dynamic_cast<T*>(component))
					return (T*)component;
			}
			return nullptr;
		}
		template <typename T> bool RemoveComponent(T* ToRemoveComponent)
		{

			for (baseComponent* component : m_Components)
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
		std::vector<baseComponent*> m_Components;
		Transform m_Transform;
	};
}
