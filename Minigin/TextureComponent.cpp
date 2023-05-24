#include "TextureComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"

using namespace dae;

TextureComponent::TextureComponent(std::string& filename, GameObject* object)
	:BaseComponent(object)
{
	
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
	m_Transform.SetPosition(object->GetWorldPos().x, object->GetWorldPos().y, object->GetWorldPos().z);
	
}
void TextureComponent::Update(float) 
{
	const auto owner = BaseComponent::GetOwner();
	m_Transform.SetPosition(owner->GetWorldPos().x, owner->GetWorldPos().y, owner->GetWorldPos().z);
}

void TextureComponent::Render() const
{
	const auto pos = m_Transform.GetPosition();
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}
void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(filename);
}
void TextureComponent::SetTransform(float x, float y, float z)
{
	m_Transform.SetPosition(x, y, z);
}
