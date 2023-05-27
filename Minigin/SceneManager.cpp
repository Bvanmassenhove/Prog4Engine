#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>

void dae::SceneManager::Update(float deltaTime)
{
	auto scene = m_scenes[m_LoadedSceneID];
	if (scene != nullptr)
	{
		scene->Update(deltaTime);
	}

	/*for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}*/
}

void dae::SceneManager::Render()
{
	auto scene = m_scenes[m_LoadedSceneID];
	if (scene != nullptr)
	{
		scene->Render();
	}

	//for (const auto& scene : m_scenes)
	//{
	//	scene->Render();
	//}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

