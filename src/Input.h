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
	Input(std::vector<Button*> buttons);

	void EnableMouseInput(bool value);
	void EnableDrawing(bool value);

	Event<>& GetKeyInputEvent(WORD key);
	Event<>& GetSpecialInputEvent(WORD specialInputType);

	void HandleInput();

	inline std::vector<IDrawable*> GetDrawables() { return m_drawables; };

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

//Globale Operatorfunktionen auﬂerhalb der Klasse definieren
inline Input::MouseInputType operator|(Input::MouseInputType leftVal, Input::MouseInputType rightVal)
{
    using T = std::underlying_type<Input::MouseInputType>::type;
    return static_cast<Input::MouseInputType>(static_cast<T>(leftVal) | static_cast<T>(rightVal));
}

inline Input::MouseInputType operator&(Input::MouseInputType leftVal, Input::MouseInputType rightVal)
{
    using T = std::underlying_type<Input::MouseInputType>::type;
    return static_cast<Input::MouseInputType>(static_cast<T>(leftVal) & static_cast<T>(rightVal));
}

inline Input::MouseInputType operator~(Input::MouseInputType val)
{
	using T = std::underlying_type<Input::MouseInputType>::type;
	return static_cast<Input::MouseInputType>(~(static_cast<T>(val)));
}