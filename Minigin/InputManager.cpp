#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>


dae::InputManager::~InputManager()
{

}

bool dae::InputManager::ProcessInput()
{

	for(auto& controller : m_pControllers)
	{
		controller.get()->Update();
		for (auto& button : m_ControllerCommandButtons)
		{
			if (button.type == InputType::Pressed && controller.get()->IsPressed(button.button))
			{
				button.pCommand.get()->Execute();
			}
		}
	}




	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
			for (auto& button : m_KeyBoardCommandButtons)
			{
				if (button.button == e.key.keysym.sym)
				{				
					button.pCommand.get()->Execute();
				}
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute();
				}
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute();
				}
				if (button.button == e.key.keysym.sym)
				{
					button.pCommand.get()->Execute();
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

	if (ID == m_pControllers.size())
	{
		m_pControllers.push_back(std::make_unique<Controller>(ID));
	}
}

void dae::InputManager::AddCommand(int ID, Controller::ControllerButton button, std::unique_ptr<Command> pCommand, InputType type)
{
	m_ControllerCommandButtons.push_back(ControllerComands{ ID, button, std::move(pCommand), type });
}

void dae::InputManager::AddCommand(int ID, SDL_Keycode button, std::unique_ptr<Command> pCommand, InputType type)
{
	m_KeyBoardCommandButtons.push_back(KeyboardComands{ ID, button, std::move(pCommand), type });
}