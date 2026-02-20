/*****************************************************************************
* Project: DrawingWorksV2
* File : Input.h
* Date : 09.09.2025
* Author : Bastian Pfaller (BP)
*
* An input class that can handle key and mouse inputs.
* It also can handle buttons that are displayed in the console.
*
* History:
* 09.09.25 BP Created
******************************************************************************/

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

	/// <summary>
	/// Creates default input handler
	/// </summary>
	Input();

	/// <summary>
	/// Creates input handler with active buttons
	/// </summary>
	/// <param name="a_buttons"></param>
	Input(std::vector<Button*> a_buttons);

	/// <summary>
	/// Enables mouse input
	/// </summary>
	/// <param name="a_value"></param>
	void EnableMouseInput(bool a_value);

	/// <summary>
	/// Enables the drawing function
	/// </summary>
	/// <param name="a_value"></param>
	void EnableDrawing(bool a_value);

	/// <summary>
	/// Handles the input
	/// </summary>
	void HandleInput();

	// Getter
	inline Event<>& GetKeyInputEvent(WORD a_key) { return m_keyInputEvents[a_key]; }
	inline Event<>& GetSpecialInputEvent(WORD a_specialInputType) { return m_specialInputEvents[a_specialInputType]; }
	inline std::vector<IDrawable*> GetDrawables() { return m_drawables; };

private:
	/// <summary>
	/// Initializes the input handler
	/// </summary>
	void Initialize();

	/// <summary>
	/// Interprets mouse input
	/// </summary>
	/// <param name="a_inputRecord"></param>
	/// <returns></returns>
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
