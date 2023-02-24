#include "Scene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_objects)
	{
		auto fpscomp = object->GetComponent<FPSComponent>();
		auto textcomp = object->GetComponent<TextComponent>();
		if (fpscomp != nullptr)fpscomp->update(deltaTime), textcomp->SetText(std::to_string(fpscomp->GetFPS()));
		if (textcomp != nullptr) textcomp->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		auto Rendercomp = object->GetComponent<TextureComponent>();
		auto textcomp = object->GetComponent<TextComponent>();
		if (Rendercomp != nullptr) Rendercomp->Render();
		if (textcomp != nullptr) textcomp->Render();
	}
}

