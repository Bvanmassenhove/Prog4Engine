#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "Controller.h"

using namespace dae;

class Controller::ControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};
		
	WORD buttonPressedThisFrame;
	WORD buttonReleasedThisFrame;

	int _controllerIndex;

public:
	ControllerImpl(int controllerIndex)
	{
		ZeroMemory(&previousState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));

		_controllerIndex = controllerIndex;
	}

	void Update()
	{
		CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &currentState);

		auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
		buttonPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
		buttonReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
	}
	bool IsDownThisFrame(unsigned int button) const { return buttonPressedThisFrame & button; }
	bool IsUpThisFrame(unsigned int button) const { return buttonReleasedThisFrame & button; }
	bool IsPressed(unsigned int button) const { return currentState.Gamepad.wButtons & button; }
};

Controller::Controller(int controllerIndex)
{
	pImpl = new ControllerImpl(controllerIndex);
}
Controller::~Controller()
{
	delete pImpl;
}

void Controller::Update()
{
	pImpl->Update();
}

bool Controller::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}
bool Controller::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}
bool Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}


