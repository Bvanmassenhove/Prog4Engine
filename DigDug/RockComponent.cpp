#include "RockComponent.h"
#include <iostream>
#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"

using namespace dae;
RockComponent::RockComponent(GameObject* object, std::string& rockfilename)
	:BaseComponent(object)
{

	if (rockfilename != "")
	{
		m_RockTexture = ResourceManager::GetInstance().LoadTexture(rockfilename);
	}

	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>();
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << "TileComponentComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
	m_X = GetOwner()->GetWorldPos().x;
	m_Y = GetOwner()->GetWorldPos().y;
}

void RockComponent::Update(float)
{
	int sceneId = SceneManager::GetInstance().GetSceneID();

	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if (collisionComponent->GetCollisionFlag() == Player && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{

		}
	}
}
void RockComponent::Render() const
{
	if (m_RockTexture != nullptr && m_Render)
	{
		Renderer::GetInstance().RenderTexture(*m_RockTexture, m_X, m_Y);
	}
}
