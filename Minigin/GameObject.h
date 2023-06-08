#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
#include "BaseComponent.h"
#include "Observer.h"
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

		

		void AddComponent(BaseComponent* component)
		{
			m_Components.push_back(component);
		}

		template <typename T> T* GetComponent() const
		{
			for (BaseComponent* component : m_Components)
			{
				if (dynamic_cast<T*>(component))
					return (T*)component;
			}
			return nullptr;
		}

		template <typename T> T* GetComponent(int compNr) const
		{
			int nr = 1;
			for (BaseComponent* component : m_Components)
			{
				if (dynamic_cast<T*>(component))
				{
					if (compNr == nr)
					{
						return (T*)component;
					}
					else
					{
					nr++;
					}
				}
				
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

		void AddObserver(Observer* observer)
		{
			m_Observers.push_back(observer);
		}
		template <typename T> bool RemoveObserver(T* ToRemoveObserver)
		{

			for (Observer* observer : m_Observers)
			{
				if (dynamic_cast<T*>(observer))
				{
					m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), ToRemoveObserver), m_Observers.end());
					return true;
				}
			}
			return false;
		}
		void NotifyObservers (int event)
		{
			for(auto observer : m_Observers) 
				observer->Notify(event,this);
		}

		void SetParent(GameObject* pParent, bool keepWorldPos);
		void SetLocalPos(const glm::vec3& pos);
		const glm::vec3& GetLocalPos() { return m_LocalTransform; };
		const glm::vec3& GetWorldPos();
		void UpdateWorldPos();
		void SetPositionDirty()
		{
			m_positionIsDirty = true;
			for (auto child : m_pchilderen)
			{
				child->SetPositionDirty();
			}
		};



	private:
		GameObject* m_pParent{ nullptr };
		std::vector <GameObject*> m_pchilderen;
		std::vector<BaseComponent*> m_Components;
		std::vector<Observer*> m_Observers;
		glm::vec3 m_WorldTransform;
		glm::vec3 m_LocalTransform;
		bool m_positionIsDirty{ true };


		void RemoveChild(GameObject* pChild) { m_pchilderen.erase(std::remove(m_pchilderen.begin(), m_pchilderen.end(), pChild), m_pchilderen.end()); }
		void AddChild(GameObject* pChild) { m_pchilderen.push_back(pChild); }
	};
}
