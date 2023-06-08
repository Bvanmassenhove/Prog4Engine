#include "TileComponent.h"
#include <iostream>
#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"

using namespace dae;
TileComponent::TileComponent(GameObject* object, std::string& Tilefilename)
	:BaseComponent(object)
{

	if (Tilefilename != "")
	{
		m_TileTexture = ResourceManager::GetInstance().LoadTexture(Tilefilename);
	}

	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>();
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << "TileComponentComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
	m_X = GetOwner()->GetWorldPos().x;
	m_Y = GetOwner()->GetWorldPos().y;
}

void TileComponent::Update(float)
{
	int sceneId = SceneManager::GetInstance().GetSceneID();

	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if (collisionComponent->GetCollisionFlag() == Player && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()) || collisionComponent->GetCollisionFlag() == Flygar && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			//GetOwner()->~GameObject();
			m_pCollisionComponent->SetCollisionFlag(Off);
			m_Render = false;
		}
	}
}
void TileComponent::Render() const
{
	if (m_TileTexture != nullptr && m_Render)
	{
		Renderer::GetInstance().RenderTexture(*m_TileTexture, m_X, m_Y);
	}
}
