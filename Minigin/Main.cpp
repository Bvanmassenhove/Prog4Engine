#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "MovementComponent.h"

using namespace dae;

void load()
{
	std::string texturepath;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& inputmanager = dae::InputManager::GetInstance();

	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 216, 180,0 });
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 80, 20,0 });
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("Programming 4 Assignment", font, go.get()));
	scene.Add(go);

	go.reset(new GameObject);
	go->AddComponent(new FPSComponent(go.get()));
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("X", font, go.get()));
	scene.Add(go);

	auto player = std::make_shared<GameObject>();
	player->SetLocalPos(glm::vec3{ 300,300,0 });
	texturepath = "Sprites/Player01.png";
	player->AddComponent(new TextureComponent{ texturepath,player.get() });
	auto movecomponent = new MovementComponent{ player.get() , 2.f };
	player->AddComponent(movecomponent);
	inputmanager.AddController(movecomponent,0,true);
	scene.Add(player);


	auto enemy = std::make_shared<GameObject>();
	enemy->SetLocalPos(glm::vec3{ 30,0,0 });
	texturepath = "Sprites/Enemy01.png";
	enemy->AddComponent(new TextureComponent{ texturepath,enemy.get() });
	auto movecomponent2 = new MovementComponent{ enemy.get() , 1.f };
	enemy->AddComponent(movecomponent2);
	inputmanager.AddController(movecomponent2, 1, false);
	scene.Add(enemy);

	//player->AddComponent(new RotationComponent{ 10.f,10.f,true, player.get() });

	/*auto enemy = new GameObject;
	enemy->SetLocalPos(glm::vec3{ 30,0,0 });
	texturepath = "Sprites/Enemy01.png";
	enemy->AddComponent(new TextureComponent{ texturepath,enemy });
	enemy->AddComponent(new RotationComponent{ 10.f,10.f,false, enemy });

	enemy->SetParent(player.get(), false);*/



}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}