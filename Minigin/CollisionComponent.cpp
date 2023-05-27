#include "CollisionComponent.h"
#include "SDL.h"
#include "Renderer.h"

using namespace dae;

CollisionComponent::CollisionComponent(GameObject* object,rectf collisionRect , CollisionFlag flag, bool DEBUG)
	:BaseComponent(object),
	m_CollisionRect(collisionRect),
	m_CollisionFlag(flag),
	m_DEBUGON(DEBUG)
{
}

void CollisionComponent::Update(float)
{
	if (m_CollisionFlag != CollisionFlag::Off && m_CollisionFlag != CollisionFlag::Level)
	{
		m_CollisionRect.bottom = GetOwner()->GetWorldPos().y ;
		m_CollisionRect.left = GetOwner()->GetWorldPos().x + 2;
	}
}

void CollisionComponent::Render() const
{
	if (m_DEBUGON)
	{
		SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 0, 0, 255);

		SDL_FRect* DrawRect = new SDL_FRect{};
		DrawRect->x = m_CollisionRect.left;
		DrawRect->y = m_CollisionRect.bottom;
		DrawRect->w = m_CollisionRect.width;
		DrawRect->h = m_CollisionRect.height;
		SDL_RenderDrawRectF(Renderer::GetInstance().GetSDLRenderer(), DrawRect);
		delete DrawRect;
	}
}

bool CollisionComponent::IsOverlap(rectf rect2)
{
	if ((m_CollisionRect.left + m_CollisionRect.width) < rect2.left || (rect2.left + rect2.width) < m_CollisionRect.left)
	{
		return false;
	}
	// If one rectangle is under the other
	if (m_CollisionRect.bottom > (rect2.bottom + rect2.height) || rect2.bottom > (m_CollisionRect.bottom + m_CollisionRect.height))
	{
		return false;
	}
	return true;
}