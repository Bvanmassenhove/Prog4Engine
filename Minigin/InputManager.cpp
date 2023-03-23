#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

dae::InputManager::InputManager()
{
	m_pControllers.push_back(std::make_unique<Controller>(0));
	m_CommandButtons.push_back(ControllerComands{Controller::ControllerButton::ButtonA,std::make_unique<Jump>(),InputType::Down});
}
dae::InputManager::~InputManager()
{

}

bool dae::InputManager::ProcessInput()
{

	for(auto& controller : m_pControllers)
	{
		controller.get()->Update();
		for (auto& button : m_CommandButtons)
		{
			if (button.type == InputType::Down && controller.get()->IsDown(button.button))
			{
				button.pCommand.get()->Excecute();
			}
		}
	}




	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}