#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>
#include "Utils.h"
#include "Event.h"
#include "IDrawable.h"


class Button : public IDrawable
{
public:
	Button(COORD* position, int width, int height, std::wstring buttonName);


	inline COORD* GetPosition() { return &m_position; }
	inline Event<>& GetOnButtonClickedEvent() { return m_onButtonClicked; }
	inline bool GetButtonHoverState() { return m_isHoveredOver; }

	virtual void Draw();

	void OnClicked();

	void OnHoveredChanged(bool value);

	bool PointInButton(COORD* coord);

private:
	COORD m_labelPosition{};
	std::wstring m_label {};

	COORD m_position{};
	int m_width{};
	int m_height{};

	Event<> m_onButtonClicked {};

	bool m_isHoveredOver { false };
};