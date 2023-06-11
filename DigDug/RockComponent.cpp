#include "RockComponent.h"
#include <iostream>
#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "LevelSelecter.h"
#include "Sounds.h"
#include "ServiceLocator.h"


using namespace dae;
RockComponent::RockComponent(GameObject* object, std::string& rockfilename)
	:BaseComponent(object)
{

	if (rockfilename != "")
	{
		m_RockTexture = ResourceManager::GetInstance().LoadTexture(rockfilename);
	}

	m_pCollisionComponent = GetOwner()->GetComponent<CollisionComponent>(1);
	if (m_pCollisionComponent == nullptr)
	{
		std::cout << "TileComponentComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
	m_pCollisionComponentDown = GetOwner()->GetComponent<CollisionComponent>(1);
	if (m_pCollisionComponentDown == nullptr)
	{
		std::cout << "TileComponentComponent Called Before CollisionComponent: CollisionComponent Not Found \n";
	}
	m_X = GetOwner()->GetWorldPos().x;
	m_Y = GetOwner()->GetWorldPos().y;
}

void RockComponent::Update(float deltaTime)
{

	//extend the collision box down ,if the collision hits anything it doesnt move
	// if it hits nothing it moves down 
	//if it has started moving and only if it has started moving it will break if it hits a tile again
	//if it hits an enemy that enemy will die
	//if it hits a player it will stop again 

	int sceneId = SceneManager::GetInstance().GetSceneID();
	m_CanFall = true;

	for (const auto& collisionComponent : CollisionManager::GetInstance().GetCollisionComponentsFromScene(sceneId))
	{
		if (collisionComponent->GetCollisionFlag() == Pooka && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			auto& soundManager = ServiceLocator::Get_Sound_System();
			soundManager.PlaySound(RockHit, 2);
			auto& sceneManager = SceneManager::GetInstance();
			int SceneID = sceneManager.GetSceneID();
			auto& loadedScene = sceneManager.LoadScene(SceneID);
			loadedScene.Remove(collisionComponent->GetComponentOwner());
		}
		else if (collisionComponent->GetCollisionFlag() == Flygar && collisionComponent->IsOverlap(m_pCollisionComponent->GetCollisionRect()))
		{
			auto& sceneManager = SceneManager::GetInstance();
			int SceneID = sceneManager.GetSceneID();
			auto& loadedScene = sceneManager.LoadScene(SceneID);
			loadedScene.Remove(collisionComponent->GetComponentOwner());
		}

		if (collisionComponent->GetCollisionFlag() == Pooka && collisionComponent->IsOverlap(m_pCollisionComponentDown->GetCollisionRect()))
		{
			m_CanFall = false;
		}
		else if (collisionComponent->GetCollisionFlag() == Flygar && collisionComponent->IsOverlap(m_pCollisionComponentDown->GetCollisionRect()))
		{
			m_CanFall = false;
		}
		else if (collisionComponent->GetCollisionFlag() == Player && collisionComponent->IsOverlap(m_pCollisionComponentDown->GetCollisionRect()))
		{
			m_CanFall = false;
		}
		else if (collisionComponent->GetCollisionFlag() == Level && collisionComponent->IsOverlap(m_pCollisionComponentDown->GetCollisionRect()))
		{
			m_CanFall = false;
		}
	}

	if (m_CanFall)
	{
		glm::vec3 pos = GetOwner()->GetLocalPos();
		GetOwner()->SetLocalPos(glm::vec3{ pos.x, pos.y += m_FallSpeed * deltaTime, pos.z });
		m_X = pos.x;
		m_Y = pos.y;
	}
}
void RockComponent::Render() const
{
	if (m_RockTexture != nullptr && m_Render)
	{
		Renderer::GetInstance().RenderTexture(*m_RockTexture, m_X, m_Y);
	}
}
