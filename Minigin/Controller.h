#pragma once
namespace dae
{
	class Controller final
	{
		class ControllerImpl;
		ControllerImpl* pImpl;
	public:
		enum class ControllerButton
		{
			DpadUp = 0x0001,
			DpadRight = 0x0008,
			DpadDown = 0x0002,
			DpadLeft = 0x0004,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x100,
			RightShoulder = 0x200
			
		};

		void Update();

		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;
		int GetControllerID() const;

		explicit Controller(int controllerIndex);
		~Controller();
	};
}
