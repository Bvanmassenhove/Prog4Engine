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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TextureComponent);
	go->GetComponent<TextureComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go.reset(new GameObject);
	go->AddComponent(new TextureComponent);
	go->GetComponent<TextureComponent>()->SetTexture("logo.tga");
	go->GetComponent<TextureComponent>()->SetTransform(216, 180, 0);
	scene.Add(go);

	go.reset(new GameObject);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	go->GetComponent<TextComponent>()->SetPosition(80, 20);
	scene.Add(go);

	go.reset(new GameObject);
	go->AddComponent(new FPSComponent);
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->AddComponent(new TextComponent("", font));
	go->GetComponent<TextComponent>()->SetPosition(0, 0);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}