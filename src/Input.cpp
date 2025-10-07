#include "Input.h"

Input::Input()
{
	Initialize();
}

Input::Input(std::vector<Button*> buttons)
{
	m_buttons = buttons;

	for (size_t i = 0; i < buttons.size(); i++)
	{
		m_drawables.push_back(buttons[i]);
	}

	Initialize();
}

void Input::Initialize()
{
	m_inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	m_outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Disable console cursor visibility
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 25;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(m_outputHandle, &cci);

	//Set new random seed
	srand(time(0));
}

void Input::EnableMouseInput(bool value)
{
	m_isMouseInputEnabled = value;
	DWORD consoleInputMode;
	if (value)
	{
		consoleInputMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;
	}
	else
	{
		consoleInputMode = (ENABLE_WINDOW_INPUT);
	}

	SetConsoleMode(m_inputHandle, consoleInputMode);
}

void Input::EnableDrawing(bool value)
{
	m_isDrawingEnabled = value;
}

Event<>& Input::GetKeyInputEvent(WORD key)
{
	return m_keyInputEvents[key];
}

Event<>& Input::GetSpecialInputEvent(WORD specialInputType)
{
	return m_specialInputEvents[specialInputType];
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
		GetKeyInputEvent(inputRecord.Event.KeyEvent.wVirtualKeyCode).Invoke();
		break;
	//Mouse event
	case MOUSE_EVENT:

		if (!m_isMouseInputEnabled) break;

		m_isButtonPressed = false;

		coord.X = inputRecord.Event.MouseEvent.dwMousePosition.X;
		coord.Y = inputRecord.Event.MouseEvent.dwMousePosition.Y;

		//Button hover handling
		for (size_t i = 0; i < m_buttons.size(); i++)
		{
			if (m_buttons[i]->PointInButton(&coord))
			{
				m_buttons[i]->OnHoveredChanged(true);
			}
			else if (!(m_buttons[i]->PointInButton(&coord)) && m_buttons[i]-> GetButtonHoverState())
			{
				m_buttons[i]->OnHoveredChanged(false);
			}
		}

		//Button click handling
		if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED || inputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			for (size_t i = 0; i < m_buttons.size(); i++)
			{
				if (m_buttons[i]->PointInButton(&coord))
				{
					m_buttons[i]->OnClicked();
					m_isButtonPressed = true;
					break;
				}
			}
		}
		if (m_isButtonPressed) break;

		if (!m_isDrawingEnabled) break;

		//Else drawing mouse input handling

		inputType = InterpretMouseInput(inputRecord);

		switch (inputType)
		{
		case MouseInputType::LeftAltLeftClick:
			Utils::DrawCircle(&coord, 4, rand() % 13 + 1);
			break;
		case MouseInputType::ShiftLeftClick:
			Utils::DrawFrameCenter(&coord, 9, 5, rand() % 13 + 1);
			break;
		case MouseInputType::LeftCtrlLeftClick:
			Utils::DrawBigX(&coord, 3, rand() % 13 + 1);
			break;
		case MouseInputType::LeftClick:
			Utils::DrawPixel(&coord, 15);
			break;
		case MouseInputType::RightClick:
			Utils::DrawPixel(&coord, rand() % 13 + 1);
			break;
		default:
			break;
		}

		//Screen resize event
	case WINDOW_BUFFER_SIZE_EVENT:
		m_wasWindowResized = true;
		break;

		//Window focus event
	case FOCUS_EVENT:
		GetSpecialInputEvent(FOCUS_EVENT).Invoke();
		break;

		//Window menu event
	case MENU_EVENT:
		GetSpecialInputEvent(MENU_EVENT).Invoke();
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
		return MouseInputType::NoClick;
		break;
	}
}

void Input::logxy(COORD coord)
{
	Utils::SetCursorPosition();
	std::cout << "X:" << coord.X << "  ";
	COORD newPos{ 7,0 };
	Utils::SetCursorPosition(&newPos);
	std::cout << "Y:" << coord.Y << "  ";
}

void Input::logRect(RECT rect)
{
	COORD newPos{ 20,0 };
	Utils::SetCursorPosition(&newPos);
	std::cout << "L:" << rect.left << "  ";
	newPos.X += 7;
	Utils::SetCursorPosition(&newPos);
	std::cout << "T:" << rect.top << "  ";
	newPos.X += 7;
	Utils::SetCursorPosition(&newPos);
	std::cout << "R:" << rect.right << "  ";
	newPos.X += 7;
	Utils::SetCursorPosition(&newPos);
	std::cout << "B:" << rect.bottom << "  ";
}