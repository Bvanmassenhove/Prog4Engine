#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltatime);
		void Render();
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

		void SetParent(GameObject* pParent, bool keepWorldPos);
		void SetLocalPos(const glm::vec3& pos);
		const glm::vec3& GetLocalPos() { return m_LocalTransform; };
		const glm::vec3& GetWorldPos();
		void UpdateWorldPos();

		

	private:
		GameObject* m_pParent{ nullptr };
		std::vector <GameObject*> m_pchilderen;
		std::vector<BaseComponent*> m_Components;
		glm::vec3 m_WorldTransform;
		glm::vec3 m_LocalTransform;
		bool m_positionIsDirty{ true };

		void RemoveChild(GameObject* pChild) { m_pchilderen.erase(std::remove(m_pchilderen.begin(), m_pchilderen.end(), pChild), m_pchilderen.end()); }
		void AddChild(GameObject* pChild) { m_pchilderen.push_back(pChild); }
	};
}
