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
	for (auto child : m_pchilderen)
	{
		delete child;
		child = nullptr;
	}
	m_pchilderen.clear();
	for (auto Observers : m_Observers)
	{
		delete Observers;
	}
	m_Observers.clear();
};

void GameObject::Update(float deltatime)
{
	for (BaseComponent* component : m_Components)
	{
		component->Update(deltatime);
	}
	if (m_pchilderen.size() != 0)
	{
		for (auto child : m_pchilderen)
		{
			child;
			child->Update(deltatime);
		}
	}
}
void GameObject::Render()
{
	for (BaseComponent* component : m_Components)
	{
		component->Render();
	}
	if (m_pchilderen.size() != 0)
	{
		for (auto child : m_pchilderen)
		{
			child->Render();
		}
	}
}
void GameObject::SetParent(GameObject* pParent, bool keepWorldPos)
{
	if (pParent == nullptr)
	{
		SetLocalPos(GetWorldPos());
	}
	else
	{
		if (keepWorldPos)
		{
			SetLocalPos(m_LocalTransform - pParent->GetWorldPos());
		}
		SetPositionDirty();
	}
	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = pParent;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}
void GameObject::SetLocalPos(const glm::vec3& pos)
{
	m_LocalTransform = pos;
	SetPositionDirty();
}
const glm::vec3& GameObject::GetWorldPos()
{
	if (m_positionIsDirty)
	{
		UpdateWorldPos();
	}
	return m_WorldTransform;
}
void GameObject::UpdateWorldPos()
{
	if (m_positionIsDirty)
	{
		if (m_pParent == nullptr)
		{
			m_WorldTransform = m_LocalTransform;
		}
		else
		{
			m_WorldTransform = m_pParent->GetWorldPos() + m_LocalTransform;
		}
	}
	m_positionIsDirty = false;
}
