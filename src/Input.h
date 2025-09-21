#pragma once

#include <vector>
#include "Event.h"
#include <Windows.h>
#include <unordered_map>
#include "Button.h"

class Input
{

public:
	enum class MouseInputType
	{
		LeftClick,
		LeftAltLeftClick,
		RightAltLeftClick,
		ShiftLeftClick,
		LeftCtrlLeftClick,
		RightCtrlLeftClick,
		RightClick,
		LeftAltRightClick,
		RightAltRightClick,
		ShiftRightClick,
		LeftCtrlRightClick,
		RightCtrlRightClick,
		MiddleClick
	};


	Input(HANDLE inputHandle, std::vector<Button*> buttons);

	Event<>* GetKeyInputEvent(WORD key);
	Event<>* GetMouseInputEvent(MouseInputType inputType);
	Event<>* GetSpecialInputEvent(WORD specialInputType);

	void HandleInput();

private:

	std::unordered_map<WORD, Event<>> m_keyInputEvents;
	std::unordered_map<MouseInputType, Event<>> m_mouseInputEvents;
	std::unordered_map<WORD, Event<>> m_specialInputEvents;

	HANDLE m_inputHandle;

	std::vector<Button*> m_buttons;

	bool m_isButtonPressed;

	MouseInputType InterpretMouseInput(INPUT_RECORD inputRecord);
};