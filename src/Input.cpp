#include "Input.h"
#include <Windows.h>

Input::Input(HANDLE inputHandle, std::vector<Button*> buttons)
{
	m_inputHandle = inputHandle;
	m_buttons = buttons;

	m_isButtonPressed = false;
}

void Input::EnableMouseInput()
{

}

Event<>* Input::GetKeyInputEvent(WORD key)
{
	return &m_keyInputEvents[key];
}

Event<>* Input::GetMouseInputEvent(MouseInputType inputType)
{
	return &m_mouseInputEvents[inputType];
}

Event<>* Input::GetSpecialInputEvent(WORD specialInputType)
{
	return &m_specialInputEvents[specialInputType];
}

void Input::HandleInput()
{
	INPUT_RECORD inputRecord;
	DWORD events;
	COORD coord;
	POINT point;
	MouseInputType inputType;

	ReadConsoleInput(m_inputHandle, &inputRecord, 1, &events);

	switch (inputRecord.EventType)
	{
		//Key event
	case KEY_EVENT:

		GetKeyInputEvent(inputRecord.Event.KeyEvent.wVirtualKeyCode)->Invoke();
		break;

		//Mouse event
	case MOUSE_EVENT:

		m_isButtonPressed = false;

		coord.X = inputRecord.Event.MouseEvent.dwMousePosition.X;
		coord.Y = inputRecord.Event.MouseEvent.dwMousePosition.Y;

		point = { coord.X, coord.Y };

		//Button hover handling
		for (size_t i = 0; i < m_buttons.size(); i++)
		{
			if (PtInRect(m_buttons[i]-> GetRect(), point))
			{
				m_buttons[i]->OnHoveredChanged(true);
			}
			else if (!PtInRect(m_buttons[i]-> GetRect(), point) && m_buttons[i]-> GetButtonHoverState())
			{
				m_buttons[i]->OnHoveredChanged(false);
			}
		}

		//Button click handling
		if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED || inputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			for (size_t i = 0; i < m_buttons.size(); i++)
			{
				if (PtInRect(m_buttons[i]-> GetRect(), point))
				{
					m_buttons[i]->OnClicked();
					m_isButtonPressed = TRUE;
					break;
				}
			}
		}
		if (m_isButtonPressed) break;

		//Else normal mouse input handling

		GetMouseInputEvent(InterpretMouseInput(inputRecord))->Invoke();
		break;

		//Screen resize event
	case WINDOW_BUFFER_SIZE_EVENT:
		GetSpecialInputEvent(WINDOW_BUFFER_SIZE_EVENT)->Invoke();
		break;

		//Window focus event
	case FOCUS_EVENT:
		GetSpecialInputEvent(FOCUS_EVENT)->Invoke();
		break;

		//Window menu event
	case MENU_EVENT:
		GetSpecialInputEvent(MENU_EVENT)->Invoke();
		break;

		//Unknown event
	default:
		break;
	}

	FlushConsoleInputBuffer(m_inputHandle);
}

Input::MouseInputType Input::InterpretMouseInput(INPUT_RECORD inputRecord)
{
	DWORD pressedControlButtonState = inputRecord.Event.MouseEvent.dwControlKeyState;

	switch (inputRecord.Event.MouseEvent.dwButtonState)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:
		if (inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_ALT_PRESSED) return MouseInputType::LeftAltLeftClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & RIGHT_ALT_PRESSED) return MouseInputType::RightAltLeftClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & SHIFT_PRESSED) return MouseInputType::ShiftLeftClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_CTRL_PRESSED) return MouseInputType::RightCtrlLeftClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & RIGHT_CTRL_PRESSED) return MouseInputType::RightCtrlLeftClick;
		return MouseInputType::LeftClick;
		break;
	case RIGHTMOST_BUTTON_PRESSED:
		if (inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_ALT_PRESSED) return MouseInputType::LeftAltRightClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & RIGHT_ALT_PRESSED) return MouseInputType::RightAltRightClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & SHIFT_PRESSED) return MouseInputType::ShiftRightClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_CTRL_PRESSED) return MouseInputType::RightCtrlRightClick;
		if (inputRecord.Event.MouseEvent.dwControlKeyState & RIGHT_CTRL_PRESSED) return MouseInputType::RightCtrlRightClick;
		return MouseInputType::RightClick;
	case FROM_LEFT_2ND_BUTTON_PRESSED:
		return MouseInputType::MiddleClick;
	default:
		break;
	}
}