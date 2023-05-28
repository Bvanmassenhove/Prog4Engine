#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <iostream>
#include <fstream>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "LevelSelecter.h"

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"

using namespace dae;
void thread_function(int x)
{
	std::cout << "inside thread x: " << ++x << "\n";
}


void load()
{
	//set total scenes for inputmanager
	auto& inputmanager = InputManager::GetInstance();
	inputmanager.SetTotalScenes(4);

	//get level selector and make the scenes
	auto& levelSelector = LevelSelecter::GetInstance();
	levelSelector.LoadScenes();

	//get and then load the main menu scene
	auto& sceneManager = SceneManager::GetInstance();
	auto& loadedScene = sceneManager.LoadScene(0);
	levelSelector.LoadMainMenu(loadedScene);

}

int main(int, char* [])
{

	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}