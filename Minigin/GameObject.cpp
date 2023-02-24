#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"

dae::GameObject::~GameObject()
{
	for (auto Component : m_Components)
	{
		delete Component;
	}
	m_Components.clear();
};

void dae::GameObject::Update()
{
	for (baseComponent* component : m_Components)
	{
		if (dynamic_cast<TextComponent*>(component))
		{
			dynamic_cast<TextComponent*>(component)->Update();
		}
	}
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(baseComponent* component)
{
	m_Components.push_back(component);
}
