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

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"

using namespace dae;

void load()
{
	std::string texturepath;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get()});
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
	player->AddComponent(new RotationComponent{ glm::vec3{0,0,0},10.f,true,10.f, player.get() });
	scene.Add(player);

	auto enemy = std::make_shared<GameObject>();
	enemy->SetParent(player.get(), false);
	enemy->SetLocalPos(glm::vec3{ 30,0,0 });
	texturepath = "Sprites/Enemy01.png";
	enemy->AddComponent(new TextureComponent{ texturepath,enemy.get() });
	enemy->AddComponent(new RotationComponent{ glm::vec3{0,0,0},10.f,false,10.f, enemy.get() });
	scene.Add(enemy);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}