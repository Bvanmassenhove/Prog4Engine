#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include <iostream>

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
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "buttonCommands.h"

#include "events.h"
#include "OnDeath.h"
#include "Achievement.h"

#include "ServiceLocator.h"


using namespace dae;
void thread_function(int x)
{
	std::cout << "inside thread x: " << ++x << "\n";
}

void LoadMainMenu()
{
	std::string texturepath;
	auto& menuScene = SceneManager::GetInstance().CreateScene("Menu");
	int SceneID = 0;
	auto& inputmanager = InputManager::GetInstance();
	
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	menuScene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 216, 10,0 });
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	menuScene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 100,0 });
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go->AddComponent(new TextComponent("Welcome to dig dug :", font, go.get()));
	menuScene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 120,0 });
	go->AddComponent(new TextComponent(" for singleplayer press either) 1 or the bottom face button ", font, go.get()));
	menuScene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 140,0 });
	go->AddComponent(new TextComponent("for Coop press either) 2 or the left face button ", font, go.get()));
	menuScene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 160,0 });
	go->AddComponent(new TextComponent("for PVP press either) 3 or the Right face button", font, go.get()));
	menuScene.Add(go);

	auto Menu = std::make_shared<GameObject>();
	int ControllerID = 0;
	inputmanager.AddController(ControllerID);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeScene>(Menu.get(),1), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_1, std::make_unique<ChangeScene>(Menu.get(),1), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<ChangeScene>(Menu.get(), 2), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_2, std::make_unique<ChangeScene>(Menu.get(), 2), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeScene>(Menu.get(), 3), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_3, std::make_unique<ChangeScene>(Menu.get(), 3), InputType::Down);
	menuScene.Add(Menu);

	//load all sounds
	ServiceLocator::Register_Sound_System(std::make_unique<SoundLogger>());
	auto& soundManager = ServiceLocator::Get_Sound_System();
	soundManager.AddSound("../Data/Sounds/DigDugShot.wav");
}

void LoadSingePlayer()
{
	std::string texturepath;
	auto& scene = SceneManager::GetInstance().CreateScene("Game : single Player");
	int SceneID = 1;
	auto& inputmanager = InputManager::GetInstance();

	///background
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 216, 180,0 });
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	//FPS counter
	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	/// player
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto player = std::make_shared<GameObject>();
	player->SetLocalPos(glm::vec3{ 300,300,0 });
	//add sprites
	auto pSprite0 = std::make_shared<Sprite>();
	pSprite0->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveRight.png");
	pSprite0->cols = 1;
	pSprite0->frames = 2;
	pSprite0->currentFrame = 0;
	pSprite0->accumulatedTime = 0.f;
	pSprite0->frameTime = 0.2f;
	player->AddComponent(new SpriteComponent(player.get(), pSprite0));

	auto pSprite1 = std::make_shared<Sprite>();
	pSprite1->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveDown.png");
	pSprite1->cols = 1;
	pSprite1->frames = 2;
	pSprite1->currentFrame = 0;
	pSprite1->accumulatedTime = 0.f;
	pSprite1->frameTime = 0.2f;
	player->GetComponent<SpriteComponent>()->AddSprite(pSprite1);

	auto pSprite2 = std::make_shared<Sprite>();
	pSprite2->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveLeft.png");
	pSprite2->cols = 1;
	pSprite2->frames = 2;
	pSprite2->currentFrame = 0;
	pSprite2->accumulatedTime = 0.f;
	pSprite2->frameTime = 0.2f;
	player->GetComponent<SpriteComponent>()->AddSprite(pSprite2);

	auto pSprite3 = std::make_shared<Sprite>();
	pSprite3->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveUp.png");
	pSprite3->cols = 1;
	pSprite3->frames = 2;
	pSprite3->currentFrame = 0;
	pSprite3->accumulatedTime = 0.f;
	pSprite3->frameTime = 0.2f;
	player->GetComponent<SpriteComponent>()->AddSprite(pSprite3);

	//score
	player->AddComponent(new TextComponent("X", font, player.get(), glm::vec3{ 0, 60,0 }));
	//health
	texturepath = "Sprites/PlayerHealth.png";
	player->AddComponent(new HealthComponent{ player.get(), 4 , texturepath ,100.f });
	player->AddObserver(new OnDeath{});

	int ControllerID = 0;
	float moveSpeed = 60.f;
	inputmanager.AddController(ControllerID);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<MoveUpDown>(player.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<MoveUpDown>(player.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<MoveLeftRight>(player.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<MoveLeftRight>(player.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(player.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(player.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(player.get()), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::Start, std::make_unique<ChangeScene>(player.get(),0), InputType::Down);
	scene.Add(player);
}

void LoadCoop()
{
	std::string texturepath;
	auto& scene = SceneManager::GetInstance().CreateScene("Game : Coop");
	int SceneID = 2;
	auto& inputmanager = InputManager::GetInstance();


	///background
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 216, 180,0 });
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	//FPS counter
	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	/// player
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto player1 = std::make_shared<GameObject>();
	auto player2 = std::make_shared<GameObject>();
	player1->SetLocalPos(glm::vec3{ 300,300,0 });
	player2->SetLocalPos(glm::vec3{ 500,300,0 });
	//add sprites
	auto pSprite0 = std::make_shared<Sprite>();
	pSprite0->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveRight.png");
	pSprite0->cols = 1;
	pSprite0->frames = 2;
	pSprite0->currentFrame = 0;
	pSprite0->accumulatedTime = 0.f;
	pSprite0->frameTime = 0.2f;
	player1->AddComponent(new SpriteComponent(player1.get(), pSprite0));
	player2->AddComponent(new SpriteComponent(player2.get(), pSprite0));

	auto pSprite1 = std::make_shared<Sprite>();
	pSprite1->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveDown.png");
	pSprite1->cols = 1;
	pSprite1->frames = 2;
	pSprite1->currentFrame = 0;
	pSprite1->accumulatedTime = 0.f;
	pSprite1->frameTime = 0.2f;
	player1->GetComponent<SpriteComponent>()->AddSprite(pSprite1);
	player2->GetComponent<SpriteComponent>()->AddSprite(pSprite1);

	auto pSprite2 = std::make_shared<Sprite>();
	pSprite2->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveLeft.png");
	pSprite2->cols = 1;
	pSprite2->frames = 2;
	pSprite2->currentFrame = 0;
	pSprite2->accumulatedTime = 0.f;
	pSprite2->frameTime = 0.2f;
	player1->GetComponent<SpriteComponent>()->AddSprite(pSprite2);
	player2->GetComponent<SpriteComponent>()->AddSprite(pSprite2);

	auto pSprite3 = std::make_shared<Sprite>();
	pSprite3->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveUp.png");
	pSprite3->cols = 1;
	pSprite3->frames = 2;
	pSprite3->currentFrame = 0;
	pSprite3->accumulatedTime = 0.f;
	pSprite3->frameTime = 0.2f;
	player1->GetComponent<SpriteComponent>()->AddSprite(pSprite3);
	player2->GetComponent<SpriteComponent>()->AddSprite(pSprite3);

	//score
	player1->AddComponent(new TextComponent("X", font, player1.get(), glm::vec3{ 0, 60,0 }));
	player2->AddComponent(new TextComponent("X", font, player2.get(), glm::vec3{ 0, 100,0 }));
	//health
	texturepath = "Sprites/PlayerHealth.png";
	player1->AddComponent(new HealthComponent{ player1.get(), 4 , texturepath ,100.f });
	player2->AddComponent(new HealthComponent{ player2.get(), 4 , texturepath ,300.f });
	player1->AddObserver(new OnDeath{});
	player2->AddObserver(new OnDeath{});

	int ControllerID = 0;
	float moveSpeed = 60.f;
	inputmanager.AddController(ControllerID);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<MoveUpDown>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<MoveUpDown>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<MoveLeftRight>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<MoveLeftRight>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(player1.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(player1.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(player1.get()), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::Start, std::make_unique<ChangeScene>(player1.get(), 0), InputType::Down);
	//Keyboard for P1
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_w, std::make_unique<MoveUpDown>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_s, std::make_unique<MoveUpDown>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_a, std::make_unique<MoveLeftRight>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_d, std::make_unique<MoveLeftRight>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_e, std::make_unique<ChangeHUD>(player1.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_r, std::make_unique<ChangeHUD>(player1.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_z, std::make_unique<Shoot>(player1.get()), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_ESCAPE, std::make_unique<ChangeScene>(player1.get(), 0), InputType::Down);


	//player 2 controlls
	ControllerID = 1;
	inputmanager.AddController(ControllerID);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<MoveUpDown>(player2.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<MoveUpDown>(player2.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<MoveLeftRight>(player2.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<MoveLeftRight>(player2.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(player2.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(player2.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(player2.get()), InputType::Down);

	scene.Add(player1);
	scene.Add(player2);
}

void LoadPVP()
{
	std::string texturepath;
	auto& scene = SceneManager::GetInstance().CreateScene("Game : PvP");
	int SceneID = 3;
	auto& inputmanager = InputManager::GetInstance();

	///background
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 216, 180,0 });
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);


	//FPS counter
	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	/// player1
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto player1 = std::make_shared<GameObject>();
	player1->SetLocalPos(glm::vec3{ 300,300,0 });
	//add sprites
	auto pSprite0 = std::make_shared<Sprite>();
	pSprite0->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveRight.png");
	pSprite0->cols = 1;
	pSprite0->frames = 2;
	pSprite0->currentFrame = 0;
	pSprite0->accumulatedTime = 0.f;
	pSprite0->frameTime = 0.2f;
	player1->AddComponent(new SpriteComponent(player1.get(), pSprite0));

	auto pSprite1 = std::make_shared<Sprite>();
	pSprite1->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveDown.png");
	pSprite1->cols = 1;
	pSprite1->frames = 2;
	pSprite1->currentFrame = 0;
	pSprite1->accumulatedTime = 0.f;
	pSprite1->frameTime = 0.2f;
	player1->GetComponent<SpriteComponent>()->AddSprite(pSprite1);

	auto pSprite2 = std::make_shared<Sprite>();
	pSprite2->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveLeft.png");
	pSprite2->cols = 1;
	pSprite2->frames = 2;
	pSprite2->currentFrame = 0;
	pSprite2->accumulatedTime = 0.f;
	pSprite2->frameTime = 0.2f;
	player1->GetComponent<SpriteComponent>()->AddSprite(pSprite2);

	auto pSprite3 = std::make_shared<Sprite>();
	pSprite3->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveUp.png");
	pSprite3->cols = 1;
	pSprite3->frames = 2;
	pSprite3->currentFrame = 0;
	pSprite3->accumulatedTime = 0.f;
	pSprite3->frameTime = 0.2f;
	player1->GetComponent<SpriteComponent>()->AddSprite(pSprite3);

	//score
	player1->AddComponent(new TextComponent("X", font, player1.get(), glm::vec3{ 0, 60,0 }));
	//health
	texturepath = "Sprites/PlayerHealth.png";
	player1->AddComponent(new HealthComponent{ player1.get(), 4 , texturepath ,100.f });
	player1->AddObserver(new OnDeath{});

	int ControllerID = 0;
	float moveSpeed = 60.f;
	inputmanager.AddController(ControllerID);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<MoveUpDown>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<MoveUpDown>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<MoveLeftRight>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<MoveLeftRight>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(player1.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(player1.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(player1.get()), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::Start, std::make_unique<ChangeScene>(player1.get(), 0), InputType::Down);
	//Keyboard for P1
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_w, std::make_unique<MoveUpDown>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_s, std::make_unique<MoveUpDown>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_a, std::make_unique<MoveLeftRight>(player1.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_d, std::make_unique<MoveLeftRight>(player1.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_e, std::make_unique<ChangeHUD>(player1.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_r, std::make_unique<ChangeHUD>(player1.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_z, std::make_unique<Shoot>(player1.get()), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_ESCAPE, std::make_unique<ChangeScene>(player1.get(), 0), InputType::Down);
	scene.Add(player1);




	/// player2
	auto player2 = std::make_shared<GameObject>();
	player2->SetLocalPos(glm::vec3{ 500,300,0 });
	//add sprites
	auto pSprite4 = std::make_shared<Sprite>();
	pSprite4->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/FlygarMoveRight.png");
	pSprite4->cols = 1;
	pSprite4->frames = 2;
	pSprite4->currentFrame = 0;
	pSprite4->accumulatedTime = 0.f;
	pSprite4->frameTime = 0.2f;
	player2->AddComponent(new SpriteComponent(player2.get(), pSprite4));
	player2->GetComponent<SpriteComponent>()->AddSprite(pSprite4);

	auto pSprite5 = std::make_shared<Sprite>();
	pSprite5->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/FlygarMoveLeft.png");
	pSprite5->cols = 1;
	pSprite5->frames = 2;
	pSprite5->currentFrame = 0;
	pSprite5->accumulatedTime = 0.f;
	pSprite5->frameTime = 0.2f;
	player2->GetComponent<SpriteComponent>()->AddSprite(pSprite5);
	player2->GetComponent<SpriteComponent>()->AddSprite(pSprite5);

	//score
	player2->AddComponent(new TextComponent("X", font, player2.get(), glm::vec3{ 0, 60,0 }));
	//health
	texturepath = "Sprites/PlayerHealth.png";
	player2->AddComponent(new HealthComponent{ player2.get(), 4 , texturepath ,100.f });
	player2->AddObserver(new OnDeath{});

	ControllerID = 1;
	inputmanager.AddController(ControllerID);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<MoveUpDown>(player2.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<MoveUpDown>(player2.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<MoveLeftRight>(player2.get(), true, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<MoveLeftRight>(player2.get(), false, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(player2.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(player2.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(player2.get()), InputType::Down);

	scene.Add(player2);
}

void load()
{
	auto& inputmanager = InputManager::GetInstance();
	inputmanager.SetTotalScenes(4);

	LoadMainMenu();
	LoadSingePlayer();
	LoadCoop();
	LoadPVP();
	//test
}

int main(int, char* [])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

	return 0;
}