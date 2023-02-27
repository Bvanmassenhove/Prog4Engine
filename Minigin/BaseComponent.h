#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
		GameObject* m_pOwner;
	public:
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float deltatime) = 0;
		virtual void Render() const = 0;

	protected:
		explicit BaseComponent(GameObject* parent) : m_pOwner(parent) {}
		const GameObject* GetOwner() { return m_pOwner; }
	};
}