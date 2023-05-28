#include "LevelSelecter.h"

#include <iostream>
#include <fstream>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "CollisionManager.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RotationComponent.h"
#include "HealthComponent.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"
#include "CollisionComponent.h"
#include "TileComponent.h"
#include "RockComponent.h"

#include "buttonCommands.h"

#include "GameEvents.h"
#include "OnDeath.h"
#include "Achievement.h"

#include "ServiceLocator.h"

using namespace dae;

std::shared_ptr<GameObject> LevelSelecter::MakePlayer(int SceneID, int ControllerID, glm::vec3 location)
{
	auto& inputmanager = InputManager::GetInstance();
	auto& collisionManager = CollisionManager::GetInstance();

	/// player
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto player = std::make_shared<GameObject>();
	player->SetLocalPos(location);
	//add sprites
	auto pSprite0 = std::make_shared<Sprite>();
	pSprite0->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PlayerMoveRight.png");
	pSprite0->cols = 1;
	pSprite0->frames = 2;
	pSprite0->currentFrame = 0;
	pSprite0->accumulatedTime = 0.f;
	pSprite0->frameTime = 0.2f;
	player->AddComponent(new SpriteComponent(player.get(), pSprite0, 2.f));

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
	std::string texturepath = "Sprites/PlayerHealth.png";
	player->AddComponent(new HealthComponent{ player.get(), 4 , texturepath ,100.f });
	player->AddObserver(new OnDeath{});


	float size = 28; // 32 - 4 to make the sprite 28/28

	rectf playerRect{ player->GetWorldPos().x + 2,player->GetWorldPos().y - 2 , size , size };
	player->AddComponent(new CollisionComponent{ player.get() ,playerRect , Player, true });
	collisionManager.AddCollisionComponent(player->GetComponent<CollisionComponent>(), SceneID);
	player->AddComponent(new PlayerComponent{ player.get(),location });

	float moveSpeed = 60.f;
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<Move>(player.get(), MoveUp, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<Move>(player.get(), MoveDown, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<Move>(player.get(), MoveLeft, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<Move>(player.get(), MoveRight, moveSpeed), InputType::Pressed);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(player.get(), true), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(player.get(), false), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(player.get()), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::Start, std::make_unique<ChangeScene>(player.get(), 0), InputType::Down);

	if (ControllerID == 0)
	{
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_w, std::make_unique<Move>(player.get(), MoveUp, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_s, std::make_unique<Move>(player.get(), MoveDown, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_a, std::make_unique<Move>(player.get(), MoveLeft, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_d, std::make_unique<Move>(player.get(), MoveRight, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_e, std::make_unique<ChangeHUD>(player.get(), true), InputType::Down);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_r, std::make_unique<ChangeHUD>(player.get(), false), InputType::Down);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_SPACE, std::make_unique<Shoot>(player.get()), InputType::Down);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_ESCAPE, std::make_unique<ChangeScene>(player.get(), 0), InputType::Down);
		inputmanager.AddCommand(SceneID, ControllerID, SDLK_F1, std::make_unique<ChangeLevel>(player.get()), InputType::Down);
	}
	return player;
}
						    
std::shared_ptr<GameObject> LevelSelecter::MakeFlygar(int SceneID, int ControllerID, glm::vec3 location, bool player)
{
	auto& inputmanager = InputManager::GetInstance();
	auto& collisionManager = CollisionManager::GetInstance();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);

	/// player2
	auto flygar = std::make_shared<GameObject>();
	flygar->SetLocalPos(location);
	//add sprites
	auto pSprite0 = std::make_shared<Sprite>();
	pSprite0->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/FlygarMoveRight.png");
	pSprite0->cols = 1;
	pSprite0->frames = 2;
	pSprite0->currentFrame = 0;
	pSprite0->accumulatedTime = 0.f;
	pSprite0->frameTime = 0.2f;
	flygar->AddComponent(new SpriteComponent(flygar.get(), pSprite0, 2.f));
	flygar->GetComponent<SpriteComponent>()->AddSprite(pSprite0);

	auto pSprite1 = std::make_shared<Sprite>();
	pSprite1->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/FlygarMoveLeft.png");
	pSprite1->cols = 1;
	pSprite1->frames = 2;
	pSprite1->currentFrame = 0;
	pSprite1->accumulatedTime = 0.f;
	pSprite1->frameTime = 0.2f;
	flygar->GetComponent<SpriteComponent>()->AddSprite(pSprite1);
	flygar->GetComponent<SpriteComponent>()->AddSprite(pSprite1);


	float size = 28; // 32 - 4 to make the sprite 28/28

	rectf flygarRect{ flygar->GetWorldPos().x + 2,flygar->GetWorldPos().y - 2,size,size };
	flygar->AddComponent(new CollisionComponent{ flygar.get() ,flygarRect , Flygar, true });
	collisionManager.AddCollisionComponent(flygar->GetComponent<CollisionComponent>(), SceneID);
	flygar->AddComponent(new PlayerComponent{ flygar.get(),location });

	if (player)
	{
		//score
		flygar->AddComponent(new TextComponent("X", font, flygar.get(), glm::vec3{ 0, 60,0 }));
		//health
		std::string texturepath = "Sprites/PlayerHealth.png";
		flygar->AddComponent(new HealthComponent{ flygar.get(), 4 , texturepath ,100.f });
		flygar->AddObserver(new OnDeath{});


		float moveSpeed = 60.f;
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadUp, std::make_unique<Move>(flygar.get(), MoveUp, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadDown, std::make_unique<Move>(flygar.get(), MoveDown, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadLeft, std::make_unique<Move>(flygar.get(), MoveLeft, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::DpadRight, std::make_unique<Move>(flygar.get(), MoveRight, moveSpeed), InputType::Pressed);
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeHUD>(flygar.get(), true), InputType::Down);
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeHUD>(flygar.get(), false), InputType::Down);
		inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<Shoot>(flygar.get()), InputType::Down);
	}


	return flygar;
}
						    
std::shared_ptr<GameObject> LevelSelecter::MakePooka(int SceneID, glm::vec3 location)
{
	auto& collisionManager = CollisionManager::GetInstance();

	auto pooka = std::make_shared<GameObject>();
	pooka->SetLocalPos(location);

	//add sprites
	auto pSprite4 = std::make_shared<Sprite>();
	pSprite4->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PookaMoveRight.png");
	pSprite4->cols = 1;
	pSprite4->frames = 2;
	pSprite4->currentFrame = 0;
	pSprite4->accumulatedTime = 0.f;
	pSprite4->frameTime = 0.2f;
	pooka->AddComponent(new SpriteComponent(pooka.get(), pSprite4, 2.f));
	pooka->GetComponent<SpriteComponent>()->AddSprite(pSprite4);

	auto pSprite5 = std::make_shared<Sprite>();
	pSprite5->texture = dae::ResourceManager::GetInstance().LoadTexture("Sprites/PookaMoveLeft.png");
	pSprite5->cols = 1;
	pSprite5->frames = 2;
	pSprite5->currentFrame = 0;
	pSprite5->accumulatedTime = 0.f;
	pSprite5->frameTime = 0.2f;
	pooka->GetComponent<SpriteComponent>()->AddSprite(pSprite5);
	pooka->GetComponent<SpriteComponent>()->AddSprite(pSprite5);

	float size = 28; // 32 - 4 to make the sprite 28/28

	rectf pookaRect{ pooka->GetWorldPos().x + 2,pooka->GetWorldPos().y - 2,size,size };
	pooka->AddComponent(new CollisionComponent{ pooka.get() ,pookaRect , Pooka, true });
	collisionManager.AddCollisionComponent(pooka->GetComponent<CollisionComponent>(), SceneID);

	return pooka;
}
						    
std::shared_ptr<GameObject> LevelSelecter::MakeRock(int SceneID, glm::vec3 location, std::string rockFile)
{
	auto& collisionManager = CollisionManager::GetInstance();

	auto rock = std::make_shared<GameObject>();
	rock->SetLocalPos(location);

	float size = 28; // 32 - 4 to make the sprite 28/28

	rectf rockRect{ rock->GetWorldPos().x + 2,rock->GetWorldPos().y - 2,size,size };
	rock->AddComponent(new CollisionComponent{ rock.get() ,rockRect , Rock, true });
	collisionManager.AddCollisionComponent(rock->GetComponent<CollisionComponent>(), SceneID);

	rock->AddComponent(new RockComponent(rock.get(), rockFile));
	return rock;
}
						    
std::shared_ptr<GameObject> LevelSelecter::MakeTile(int SceneID, glm::vec3 location, std::string tileFile)
{
	auto& collisionManager = CollisionManager::GetInstance();

	auto tile = std::make_shared<GameObject>();
	tile->SetLocalPos(location);

	float size = 28; // 32 - 4 to make the sprite 28/28

	rectf tileRect{ tile->GetWorldPos().x + 2,tile->GetWorldPos().y - 2,size,size };
	tile->AddComponent(new CollisionComponent{ tile.get() ,tileRect , Level, false });
	collisionManager.AddCollisionComponent(tile->GetComponent<CollisionComponent>(), SceneID);

	tile->AddComponent(new TileComponent(tile.get(), tileFile));

	return tile;
}

void LevelSelecter::LoadLevel(int LevelID, dae::Scene& scene, int SceneID)
{
	auto dataPath = dae::ResourceManager::GetInstance().GetDataPath();
	std::string levelPath;

	//the level .txt files were made by Catherine Szobel then modified by me
	switch (LevelID)
	{
	case 1:
		levelPath = "Levels/Level1.txt";
		break;
	case 2:
		levelPath = "Levels/Level2.txt";
		break;
	case 3:
		levelPath = "Levels/Level3.txt";
		break;
	case 4:
		levelPath = "Levels/Level4.txt";
		break;
	case 5:
		levelPath = "Levels/Level5.txt";
		break;
	default:
		std::cout << "levelID not found \n";
		break;
	}

	std::ifstream LevelFile(dataPath + levelPath);

	int readValue = 0;
	int XIndex = 0, YIndex = 0;
	const int LevelCol = 20;
	const float startingPosX = -32.f, startingPosY = 160.f;
	const float TileWith = 32.f, TileHight = 32.f;
	int TileType = 1;

	//personal codex
	//0 = blank
	//1 = tile
	//2 = player1
	//3 = player2
	//4 = pooka
	//5 = Flygar
	//6 = FlygarPlayer2
	//7 = Rock

	while (LevelFile >> readValue)
	{
		switch (readValue)
		{
		case 0:
			++XIndex;
			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}
			break;
		case 1:
			++XIndex;

			switch (TileType)
			{
			case 1:
				scene.Add(MakeTile(SceneID, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, dataPath + "Sprites/LevelTiles/TileLayer1.png"));
				break;
			case 2:
				scene.Add(MakeTile(SceneID, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, dataPath + "Sprites/LevelTiles/TileLayer2.png"));
				break;
			case 3:
				scene.Add(MakeTile(SceneID, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, dataPath + "Sprites/LevelTiles/TileLayer3.png"));
				break;
			case 4:
				scene.Add(MakeTile(SceneID, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, dataPath + "Sprites/LevelTiles/TileLayer4.png"));
				break;
			default:
				break;
			}

			if (XIndex % 20 == 0 && YIndex % 3 == 0 && YIndex != 0)
			{
				++TileType;
			}

			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}

			break;
		case 2:
			++XIndex;

			scene.Add(MakePlayer(SceneID, 0, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }));

			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}

			break;
		case 3:
			++XIndex;

			scene.Add(MakePlayer(SceneID, 1, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }));



			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}
			break;
		case 4:
			++XIndex;

			scene.Add(MakePooka(SceneID, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }));


			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}
			break;
		case 5:
			++XIndex;

			scene.Add(MakeFlygar(SceneID, 0, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, false));

			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}
			break;
		case 6:
			++XIndex;

			scene.Add(MakeFlygar(SceneID, 1, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, true));

			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}
			break;
		case 7:
			++XIndex;

			scene.Add(MakeRock(SceneID, { startingPosX + (TileWith * XIndex) , startingPosY + (TileHight * (YIndex - 1)),0.f }, dataPath + "Sprites/Rock.png"));

			if (XIndex >= LevelCol)
			{
				++YIndex;
				XIndex = 0;
			}
			break;
		default:
			std::cout << "levelID not found \n";
			break;
		}
	}
}

void LevelSelecter::LoadScenes()
{
	SceneManager::GetInstance().CreateScene("Menu");
	SceneManager::GetInstance().CreateScene("Game : single Player");
	SceneManager::GetInstance().CreateScene("Game : Coop");
	SceneManager::GetInstance().CreateScene("Game : PvP");

	//load all sounds
	ServiceLocator::Register_Sound_System(std::make_unique<SoundLogger>());
	auto& soundManager = ServiceLocator::Get_Sound_System();
	soundManager.AddSound("../Data/Sounds/DigDugShot.wav");
	soundManager.AddSound("../Data/Sounds/GetHitSound.wav");


	auto& inputmanager = InputManager::GetInstance();
	inputmanager.AddController(0);
	inputmanager.AddController(1);
}

void LevelSelecter::LoadMainMenu(dae::Scene& scene)
{
	std::string texturepath;
	int SceneID = 0;

	scene.RemoveAll();

	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 216, 10,0 });
	texturepath = "logo.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 100,0 });
	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	go->AddComponent(new TextComponent("Welcome to dig dug :", font, go.get()));
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 120,0 });
	go->AddComponent(new TextComponent(" for singleplayer press either) 1 or the bottom face button ", font, go.get()));
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 140,0 });
	go->AddComponent(new TextComponent("for Coop press either) 2 or the left face button ", font, go.get()));
	scene.Add(go);

	go.reset(new GameObject);
	go->SetLocalPos(glm::vec3{ 100, 160,0 });
	go->AddComponent(new TextComponent("for PVP press either) 3 or the Right face button", font, go.get()));
	scene.Add(go);

	auto& inputmanager = InputManager::GetInstance();
	inputmanager.ResetCommandsForScene(SceneID);

	auto Menu = std::make_shared<GameObject>();
	int ControllerID = 0;
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonA, std::make_unique<ChangeScene>(Menu.get(), 1), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_1, std::make_unique<ChangeScene>(Menu.get(), 1), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonX, std::make_unique<ChangeScene>(Menu.get(), 2), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_2, std::make_unique<ChangeScene>(Menu.get(), 2), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, Controller::ControllerButton::ButtonB, std::make_unique<ChangeScene>(Menu.get(), 3), InputType::Down);
	inputmanager.AddCommand(SceneID, ControllerID, SDLK_3, std::make_unique<ChangeScene>(Menu.get(), 3), InputType::Down);
	scene.Add(Menu);
}

void LevelSelecter::LoadSingePlayer(int levelID , dae::Scene& scene)
{
	std::string texturepath;
	
	int SceneID = 1;

	m_loadedLevel = levelID;

	scene.RemoveAll();

	///background
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	//FPS counter
	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	auto& inputmanager = InputManager::GetInstance();
	inputmanager.ResetCommandsForScene(SceneID);

	auto& collisionmanager = CollisionManager::GetInstance();
	collisionmanager.ClearCollisionComponentsFromScene(SceneID);

	LoadLevel(levelID, scene, SceneID);
}

void LevelSelecter::LoadCoop(int levelID, dae::Scene& scene)
{
	std::string texturepath;

	int SceneID = 2;

	m_loadedLevel = levelID;

	scene.RemoveAll();

	///background
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);

	//FPS counter
	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	auto& inputmanager = InputManager::GetInstance();
	inputmanager.ResetCommandsForScene(SceneID);

	auto& collisionmanager = CollisionManager::GetInstance();
	collisionmanager.ClearCollisionComponentsFromScene(SceneID);

	LoadLevel(levelID, scene, SceneID);
}

void LevelSelecter::LoadPVP(int levelID, dae::Scene& scene)
{
	std::string texturepath;
	int SceneID = 3;

	m_loadedLevel = levelID;

	scene.RemoveAll();

	///background
	auto go = std::make_shared<GameObject>();
	texturepath = "background.tga";
	go->AddComponent(new TextureComponent{ texturepath,go.get() });
	scene.Add(go);


	//FPS counter
	auto FPS = std::make_shared<GameObject>();
	FPS->AddComponent(new FPSComponent(FPS.get()));
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	FPS->AddComponent(new TextComponent("X", font, FPS.get()));
	scene.Add(FPS);

	auto& inputmanager = InputManager::GetInstance();
	inputmanager.ResetCommandsForScene(SceneID);

	auto& collisionmanager = CollisionManager::GetInstance();
	collisionmanager.ClearCollisionComponentsFromScene(SceneID);

	LoadLevel(levelID, scene, SceneID);
}