#include "SpriteComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

using namespace dae;

SpriteComponent::SpriteComponent(GameObject* object, std::shared_ptr<Sprite> sprite,float scale)
	:BaseComponent(object),
	m_Scale(scale)
{
	m_Transform.SetPosition(object->GetWorldPos().x, object->GetWorldPos().y, object->GetWorldPos().z);

	
	AddSprite(sprite);
}
SpriteComponent::~SpriteComponent()
{

}
void SpriteComponent::Update(float deltatime)
{
	const auto owner = BaseComponent::GetOwner();
	m_Transform.SetPosition(owner->GetWorldPos().x, owner->GetWorldPos().y, owner->GetWorldPos().z);

	m_Sprites[m_CurrentAnimation]->accumulatedTime += deltatime;
	if (m_Sprites[m_CurrentAnimation]->accumulatedTime > m_Sprites[m_CurrentAnimation]->frameTime)
	{
		++m_Sprites[m_CurrentAnimation]->currentFrame %= m_Sprites[m_CurrentAnimation]->frames;
		m_Sprites[m_CurrentAnimation]->accumulatedTime -= m_Sprites[m_CurrentAnimation]->frameTime;
	}
}

void SpriteComponent::Render() const
{
	const auto pos = m_Transform.GetPosition();
	dae::Renderer::GetInstance().RenderSprite(*m_Sprites[m_CurrentAnimation]->texture.get(), pos.x, pos.y,
		m_Sprites[m_CurrentAnimation]->spriteSize.first * m_Sprites[m_CurrentAnimation]->currentFrame, 
		m_Sprites[m_CurrentAnimation]->spriteSize.second * 0.f, m_Sprites[m_CurrentAnimation]->spriteSize.first,
		m_Sprites[m_CurrentAnimation]->spriteSize.second, m_Scale);
}

void SpriteComponent::AddSprite(std::shared_ptr<Sprite> sprite)
{
	sprite->spriteSize = { float(sprite->texture->GetSize().x / sprite->frames) ,float(sprite->texture->GetSize().y / sprite->cols) };
	m_Sprites.push_back(sprite);
}

void SpriteComponent::SetTransform(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}
