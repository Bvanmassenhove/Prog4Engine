#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <SDL.h>
#include <vector>
#include "ButtonCommands.h"
#include "Singleton.h"
#include "controller.h"


namespace dae
{
	enum class InputType
	{
		Up,
		Down,
		Pressed
	};
	struct ControllerComands
	{
		Controller::ControllerButton button;
		std::unique_ptr<Command > pCommand;
		InputType type;
	};
	class InputManager final : public Singleton<InputManager>
	{
		XINPUT_STATE m_CurrentState{};
		XINPUT_KEYSTROKE m_CurrentKeyStroke{};
		SDL_Event m_SDLEvent{};

		std::vector<std::unique_ptr<Controller>> m_pControllers;
		std::vector<ControllerComands> m_CommandButtons;
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();

	};

}
