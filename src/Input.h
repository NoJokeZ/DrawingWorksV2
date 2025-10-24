#pragma once

#include <vector>
#include "Event.h"
#include <Windows.h>
#include <unordered_map>
#include "Button.h"

class Input
{
public:
	enum class MouseInputType : char
	{
		NoClick		= 0,
		LeftClick	= 1,
		RightClick	= 2,
		MiddleClick = 4,
		LeftAlt		= 8,
		RightAlt	= 16,
		Shift		= 32,
		LeftCtrl	= 64,
		RightCtrl	= 128
	};

	Input();
	Input(std::vector<Button*> a_buttons);

	void EnableMouseInput(bool a_value);
	void EnableDrawing(bool a_value);

	Event<>& GetKeyInputEvent(WORD a_key);
	Event<>& GetSpecialInputEvent(WORD a_specialInputType);

	void HandleInput();

	inline std::vector<IDrawable*> GetDrawables() { return m_drawables; };

private:
	void Initialize();

	MouseInputType InterpretMouseInput(INPUT_RECORD a_inputRecord);

	std::unordered_map<WORD, Event<>> m_keyInputEvents{};
	std::unordered_map<WORD, Event<>> m_specialInputEvents{};

	HANDLE m_inputHandle{};
	HANDLE m_outputHandle{};

	std::vector<Button*> m_buttons{};

	std::vector<IDrawable*> m_drawables{};

	bool m_isButtonPressed{ false };

	bool m_wasWindowResized{ false };

	bool m_isMouseInputEnabled{ false };
	bool m_isDrawingEnabled{ false };
};
