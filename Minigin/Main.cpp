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
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	go->GetComponent<TextureComponent>()->SetTransform(216, 180, 0);
	scene.Add(go);

	go.reset(new GameObject);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("Programming 4 Assignment", font, go.get()));
	go->GetComponent<TextComponent>()->SetPosition(80, 20);
	scene.Add(go);

	go.reset(new GameObject);
	go->AddComponent(new FPSComponent(go.get()));
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("X", font, go.get()));
	go->GetComponent<TextComponent>()->SetPosition(0, 0);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}