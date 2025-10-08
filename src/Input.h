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
		NoClick,
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


	Input();
	Input(std::vector<Button*> buttons);

	void EnableMouseInput(bool value);
	void EnableDrawing(bool value);

	Event<>& GetKeyInputEvent(WORD key);
	Event<>& GetSpecialInputEvent(WORD specialInputType);

	void HandleInput();

	inline std::vector<IDrawable*> GetDrawables() { return m_drawables; };

	void logxy(COORD coord);
	void logRect(RECT rect);

private:
	void Initialize();

	MouseInputType InterpretMouseInput(INPUT_RECORD inputRecord);

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