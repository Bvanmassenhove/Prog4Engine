#pragma once
#include <iostream>

#include <SDL.h>
#include <iostream>
#include <fstream>
#include "Singleton.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "GameObject.h"


namespace dae
{
	class LevelSelecter final : public Singleton<LevelSelecter>
	{
	public:
		LevelSelecter() = default;
		virtual ~LevelSelecter() = default;
		LevelSelecter(const LevelSelecter& other) = delete;
		LevelSelecter(LevelSelecter&& other) = delete;
		LevelSelecter& operator=(const LevelSelecter& other) = delete;
		LevelSelecter& operator=(LevelSelecter&& other) = delete;

		int GetLoadedLevel() { return m_loadedLevel; }
		void SetLoadedLevel(int newLoadedLevel) { m_loadedLevel = newLoadedLevel; }


		void LoadScenes();
		void LoadMainMenu(dae::Scene& scene);
		void LoadSingePlayer(int levelID, dae::Scene& scene);
		void LoadCoop(int levelID, dae::Scene& scene);
		void LoadPVP(int levelID, dae::Scene& scene);

	private:
		std::shared_ptr<GameObject> MakePlayer(int SceneID, int ControllerID, glm::vec3 location);
		std::shared_ptr<GameObject> MakeFlygar(int SceneID, int ControllerID, glm::vec3 location, bool player);
		std::shared_ptr<GameObject> MakePooka(int SceneID, glm::vec3 location);
		std::shared_ptr<GameObject> MakeRock(int SceneID, glm::vec3 location, std::string rockFile);
		std::shared_ptr<GameObject> MakeTile(int SceneID, glm::vec3 location, std::string tileFile);

		void LoadLevel(int LevelID, dae::Scene& scene, int SceneID);

		int m_loadedLevel = 1;
		int m_LoadedScene = 0;
	};
}

