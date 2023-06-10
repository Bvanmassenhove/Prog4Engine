#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();
		
		void SetGameMode(std::shared_ptr<GameObject> object);
		GameObject* GetGameMode() {return  m_GameMode.get();}

		void Update(float deltaTime);
		void Render() const;

		void PauseUpdate( bool pause) { m_PauseUpdate = pause; }
		void AddEnemy() { m_Enemies++; }
		void RemoveEnemy() { m_Enemies--; }
		int GetRemainingEnemies() { return m_Enemies; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_name;
		std::shared_ptr<GameObject> m_GameMode{};
		std::vector <std::shared_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter; 

		bool m_PauseUpdate{ false };
		int m_Enemies{ 0 };
	};

}
