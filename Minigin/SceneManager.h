#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update(float deltaTime);
		void Render();
		void LoadScene(int SceneID) { m_LoadedSceneID = SceneID; };
		int GetSceneID() { return m_LoadedSceneID; };

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		int m_LoadedSceneID = 0;
	};
}
