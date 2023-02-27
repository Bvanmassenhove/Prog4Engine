#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"

using namespace dae;

GameObject::~GameObject()
{
	for (auto Component : m_Components)
	{
		delete Component;
	}
	m_Components.clear();
};

void GameObject::Update(float deltatime)
{
	for (BaseComponent* component : m_Components)
	{
		component->Update(deltatime);
	}
}
void GameObject::Render()
{
	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void GameObject::AddComponent(BaseComponent* component)
{
	m_Components.push_back(component);
}
