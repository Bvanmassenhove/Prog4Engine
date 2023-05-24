#include <SDL.h>
#include "InputManager.h"
#include <iostream>
#include <backends/imgui_impl_sdl2.h>
#include "SceneManager.h"

dae::InputManager::~InputManager()
{

}

void dae::InputManager::SetTotalScenes(int NrScene)
{
	for (size_t i = 0; i < NrScene; i++)
	{
		m_ControllerCommandButtons.push_back(std::vector<ControllerComands>{});
		m_KeyBoardCommandButtons.push_back(std::vector<KeyboardComands>{});
	}
}

bool dae::InputManager::ProcessInput(float deltaTime)
{
	auto& sceneManager = SceneManager::GetInstance();
	int SceneID = sceneManager.GetSceneID();

	for (auto& controller : m_pControllers)
	{
		controller.get()->Update();
		for (auto& button : m_ControllerCommandButtons[SceneID])
		{
			if (button.ControllerID == controller.get()->GetControllerID())
			{
				if (button.type == InputType::Pressed && controller.get()->IsPressed(button.button))
				{
					button.pCommand.get()->Execute(deltaTime);
				}
				if (button.type == InputType::Down && controller.get()->IsDown(button.button))
				{
					button.pCommand.get()->Execute(deltaTime);
				}
				if (button.type == InputType::Up && controller.get()->IsUp(button.button))
				{
					button.pCommand.get()->Execute(deltaTime);
				}
			}
		}
	}


	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

			for (auto& button : m_KeyBoardCommandButtons[SceneID])
			{
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute(deltaTime);
				}
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute(deltaTime);
				}
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute(deltaTime);
				}
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute(deltaTime);
				}
			}

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::AddController(int ID)
{

	if (ID == int(m_pControllers.size()))
	{
		m_pControllers.push_back(std::make_unique<Controller>(ID));
	}
}

void dae::InputManager::AddCommand(int SceneID, int ControllerID, Controller::ControllerButton button, std::unique_ptr<Command> pCommand, InputType type)
{
	m_ControllerCommandButtons[SceneID].push_back(ControllerComands{ ControllerID, button, std::move(pCommand), type});
}

void dae::InputManager::AddCommand(int SceneID, int ControllerID, SDL_Keycode button, std::unique_ptr<Command> pCommand, InputType type)
{
	m_KeyBoardCommandButtons[SceneID].push_back(KeyboardComands{ ControllerID, button, std::move(pCommand), type });
}