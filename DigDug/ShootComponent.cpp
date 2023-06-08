#include "ShootComponent.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include <iostream>

using namespace dae;

ShootComponent::ShootComponent(GameObject* object, std::string& arrowRightFilePath, std::string& arrowLeftFilePath, std::string& arrowUpFilePath, std::string& arrowDownFilePath,float with, float maxLenght,float shotSpeedMulti, float offset)
	:BaseComponent(object),
	m_With(with),
	m_MaxLenght(maxLenght),
	m_ShootSpeedMulti(shotSpeedMulti),
	m_Offset(offset)
{
	m_Arrows.emplace_back(ResourceManager::GetInstance().LoadTexture(arrowRightFilePath));
	m_Arrows.emplace_back(ResourceManager::GetInstance().LoadTexture(arrowLeftFilePath));
	m_Arrows.emplace_back(ResourceManager::GetInstance().LoadTexture(arrowUpFilePath));
	m_Arrows.emplace_back(ResourceManager::GetInstance().LoadTexture(arrowDownFilePath));

	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>(2);
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << "PlayerComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
}
void ShootComponent::Update(float deltatime)
{
	m_PosX = GetOwner()->GetWorldPos().x + m_Offset;
	m_PosY = GetOwner()->GetWorldPos().y + m_Offset;

	
	if (m_Shooting)
	{
		rectf collision;

		int sceneId = SceneManager::GetInstance().GetSceneID();
		for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
		{
			if (collisionComponent->GetCollisionFlag() == Pooka && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()) )
			{
				m_Shooting = false;
				m_Hit = collisionComponent->GetComponentOwner();
			}
			if (m_pCollisionComponent->GetCollisionFlag() == Arrow && collisionComponent->GetCollisionFlag() == Flygar && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
			{
				m_Shooting = false;
				m_Hit = collisionComponent->GetComponentOwner();
			}
			if (m_pCollisionComponent->GetCollisionFlag() == Flame && collisionComponent->GetCollisionFlag() == Player && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
			{
				m_Shooting = false;
				m_Hit = collisionComponent->GetComponentOwner();
			}
			if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect())|| collisionComponent->GetCollisionFlag() == Rock && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
			{
				Reset();
				return;
			}
		}


		if (m_Lenght < m_MaxLenght)
		{
			m_Lenght += deltatime * m_ShootSpeedMulti;
		}
		else
		{
			Reset();
			return;
		}

		

		switch (m_Direction)
		{
		case right:
			Renderer::GetInstance().RenderTexture(*m_Arrows[0], m_PosX, m_PosY, m_Lenght, m_With);
			collision = { m_PosX, m_PosY, m_Lenght, m_With };
			m_pCollisionComponent->SetCollisionRect(collision);
			break;
		case left:
			Renderer::GetInstance().RenderTexture(*m_Arrows[1], m_PosX - m_Lenght, m_PosY, m_Lenght, m_With);
			collision = { m_PosX - m_Lenght, m_PosY, m_Lenght, m_With };
			m_pCollisionComponent->SetCollisionRect(collision);
			break;
		case up:
			Renderer::GetInstance().RenderTexture(*m_Arrows[2], m_PosX, m_PosY - m_Lenght, m_With, m_Lenght);
			collision = { m_PosX, m_PosY - m_Lenght, m_With, m_Lenght };
			m_pCollisionComponent->SetCollisionRect(collision);
			break;
		case down:
			Renderer::GetInstance().RenderTexture(*m_Arrows[3], m_PosX, m_PosY, m_With, m_Lenght);
			collision = { m_PosX, m_PosY, m_With, m_Lenght };
			m_pCollisionComponent->SetCollisionRect(collision);
			break;
		default:
			break;
		}
		
	}
}
void ShootComponent::Render() const
{
	if (m_Shooting || m_Hit)
	{
		switch (m_Direction)
		{
		case right:
			Renderer::GetInstance().RenderTexture(*m_Arrows[0], m_PosX, m_PosY, m_Lenght, m_With);
			break;
		case left:
			Renderer::GetInstance().RenderTexture(*m_Arrows[1], m_PosX - m_Lenght, m_PosY, m_Lenght, m_With);
			break;
		case up:
			Renderer::GetInstance().RenderTexture(*m_Arrows[2], m_PosX, m_PosY - m_Lenght, m_With, m_Lenght);
			break;
		case down:
			Renderer::GetInstance().RenderTexture(*m_Arrows[3], m_PosX, m_PosY, m_With, m_Lenght);
			break;
		default:
			break;
		}
	}
}

