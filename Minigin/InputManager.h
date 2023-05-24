#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <SDL.h>
#include <vector>
#include <memory>
#include "Command.h"
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
		int ControllerID;
		Controller::ControllerButton button;
		
		std::unique_ptr<Command> pCommand;
		InputType type;
	};
	struct KeyboardComands
	{
		int ControllerID;
		SDL_Keycode button;
		std::unique_ptr<Command> pCommand;
		InputType type;
	};
	class InputManager final : public Singleton<InputManager>
	{
		XINPUT_STATE m_CurrentState{};
		XINPUT_KEYSTROKE m_CurrentKeyStroke{};
		SDL_Event m_SDLEvent{};

		std::vector<std::unique_ptr<Controller>> m_pControllers;
		std::vector<std::vector<ControllerComands>> m_ControllerCommandButtons;
		std::vector<std::vector<KeyboardComands>> m_KeyBoardCommandButtons;
	public:
		InputManager() = default;
		~InputManager();
		bool ProcessInput(float deltaTime);
		void AddController(int ID);
		void SetTotalScenes(int NrScene);
		void AddCommand(int SceneID, int ControllerID, Controller::ControllerButton button, std::unique_ptr<Command> pCommand, InputType type);
		void AddCommand(int SceneID, int ControllerID, SDL_Keycode button, std::unique_ptr<Command> pCommand, InputType type);
	};

}
