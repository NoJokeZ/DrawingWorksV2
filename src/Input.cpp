#include "Input.h"

#pragma region Enum operator functions
Input::MouseInputType operator|(Input::MouseInputType leftVal, Input::MouseInputType rightVal)
{
	using T = std::underlying_type<Input::MouseInputType>::type;
	return static_cast<Input::MouseInputType>(static_cast<T>(leftVal) | static_cast<T>(rightVal));
}

Input::MouseInputType operator&(Input::MouseInputType leftVal, Input::MouseInputType rightVal)
{
	using T = std::underlying_type<Input::MouseInputType>::type;
	return static_cast<Input::MouseInputType>(static_cast<T>(leftVal) & static_cast<T>(rightVal));
}

Input::MouseInputType operator~(Input::MouseInputType val)
{
	using T = std::underlying_type<Input::MouseInputType>::type;
	return static_cast<Input::MouseInputType>(~(static_cast<T>(val)));
}
#pragma endregion


Input::Input()
{
	Initialize();
}

Input::Input(std::vector<Button*> a_buttons)
{
	m_buttons = a_buttons;

	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		m_drawables.push_back(m_buttons[i]);
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

void Input::EnableMouseInput(bool a_value)
{
	m_isMouseInputEnabled = a_value;
	DWORD consoleInputMode;
	if (m_isMouseInputEnabled)
	{
		consoleInputMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;
	}
	else
	{
		consoleInputMode = (ENABLE_WINDOW_INPUT);
	}

	SetConsoleMode(m_inputHandle, consoleInputMode);
}

void Input::EnableDrawing(bool a_value)
{
	m_isDrawingEnabled = a_value;
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
			else if (!(m_buttons[i]->PointInButton(&coord)) && m_buttons[i]->GetButtonHoverState())
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

		if (static_cast<bool>(inputType & MouseInputType::LeftClick))
		{
			inputType = inputType & ~MouseInputType::LeftClick;

			switch (inputType)
			{
			case MouseInputType::LeftAlt:
				Utils::DrawCircle(&coord, 4, rand() % 13 + 1);
				break;
			case MouseInputType::Shift:
				Utils::DrawFrameCenter(&coord, 9, 5, rand() % 13 + 1);
				break;
			case MouseInputType::LeftCtrl:
				Utils::DrawBigX(&coord, 3, rand() % 13 + 1);
				break;
			default:
				Utils::DrawPixel(&coord, 15);
				break;
			}
		}
		else if (static_cast<bool>(inputType & MouseInputType::RightClick))
		{
			inputType = inputType & ~MouseInputType::RightClick;

			switch (inputType)
			{
			case MouseInputType::LeftAlt:
				//Not used yet
				break;
			case MouseInputType::Shift:
				//Not used yet
				break;
			case MouseInputType::LeftCtrl:
				//Not used yet
				break;
			default:
				Utils::DrawPixel(&coord, rand() % 13 + 1);
				break;
			}
		}
		else if (static_cast<bool>(inputType & MouseInputType::MiddleClick))
		{
			inputType = inputType & ~MouseInputType::MiddleClick;

			switch (inputType)
			{
			case MouseInputType::LeftAlt:
				//Not used yet
				break;
			case MouseInputType::Shift:
				//Not used yet
				break;
			case MouseInputType::LeftCtrl:
				//Not used yet
				break;
			default:
				//Not used yet
				break;
			}
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

Input::MouseInputType Input::InterpretMouseInput(INPUT_RECORD a_inputRecord)
{
	MouseInputType inputType;

	switch (a_inputRecord.Event.MouseEvent.dwButtonState)
	{
	case FROM_LEFT_1ST_BUTTON_PRESSED:
		inputType = MouseInputType::LeftClick;
		break;
	case RIGHTMOST_BUTTON_PRESSED:
		inputType = MouseInputType::RightClick;
		break;
	case FROM_LEFT_2ND_BUTTON_PRESSED:
		inputType = MouseInputType::MiddleClick;
	default:
		inputType = MouseInputType::NoClick;
		//If no mouse button was clicked we return directly with only NoClick;
		return inputType;
		break;
	}

	if (a_inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_ALT_PRESSED)
	{
		inputType = inputType | MouseInputType::LeftAlt;
	}
	else if (a_inputRecord.Event.MouseEvent.dwControlKeyState & RIGHT_ALT_PRESSED)
	{
		inputType = inputType | MouseInputType::RightAlt;
	}
	else if (a_inputRecord.Event.MouseEvent.dwControlKeyState & SHIFT_PRESSED)
	{
		inputType = inputType | MouseInputType::Shift;
	}
	else if (a_inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_CTRL_PRESSED)
	{
		inputType = inputType | MouseInputType::LeftCtrl;
	}
	else if (a_inputRecord.Event.MouseEvent.dwControlKeyState & RIGHT_CTRL_PRESSED)
	{
		inputType = inputType | MouseInputType::RightCtrl;
	}

	return inputType;
}