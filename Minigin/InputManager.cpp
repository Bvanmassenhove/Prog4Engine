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

void dae::InputManager::AddController(MovementComponent* moveComponent, int ID,bool isController)
{
	m_pControllers.push_back(std::make_unique<Controller>(ID));
	if (isController)
	{
		//command buttons get added when more controllers are added ... maybe move command buttons into the controller object instead
		m_ControllerCommandButtons.push_back(ControllerComands{ Controller::ControllerButton::DpadUp,std::make_unique<MoveUp>(moveComponent),InputType::Pressed });
		m_ControllerCommandButtons.push_back(ControllerComands{ Controller::ControllerButton::DpadLeft,std::make_unique<MoveLeft>(moveComponent),InputType::Pressed });
		m_ControllerCommandButtons.push_back(ControllerComands{ Controller::ControllerButton::DpadRight,std::make_unique<MoveRight>(moveComponent),InputType::Pressed });
		m_ControllerCommandButtons.push_back(ControllerComands{ Controller::ControllerButton::DpadDown,std::make_unique<MoveDown>(moveComponent),InputType::Pressed });
	}
	else
	{
		//command buttons get added when more controllers are added ... maybe move command buttons into the controller object instead
		m_KeyBoardCommandButtons.push_back(KeyboardComands{ SDLK_w,std::make_unique<MoveUp>(moveComponent),InputType::Pressed });
		m_KeyBoardCommandButtons.push_back(KeyboardComands{ SDLK_a,std::make_unique<MoveLeft>(moveComponent),InputType::Pressed });
		m_KeyBoardCommandButtons.push_back(KeyboardComands{ SDLK_d,std::make_unique<MoveRight>(moveComponent),InputType::Pressed });
		m_KeyBoardCommandButtons.push_back(KeyboardComands{ SDLK_s,std::make_unique<MoveDown>(moveComponent),InputType::Pressed });
	}
	
}