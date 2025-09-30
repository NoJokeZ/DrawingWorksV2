#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <windows.h>
#include "Utils.h"
#include "Event.h"

class Button
{
public:
	Button(RECT* rect, std::wstring buttonName);

	inline RECT* GetRect() { return m_rect; }
	inline Event<>& GetOnButtonClickedEvent() { return m_onButtonClicked; }
	inline bool GetButtonHoverState() { return m_isHoveredOver; }

	void DrawMe();

	void OnClicked();

	void OnHoveredChanged(bool value);

private:
	int m_labelX { 0 };
	int m_labelY { 0 };

	std::wstring m_label {};

	RECT* m_rect { nullptr };

	Event<> m_onButtonClicked {};

	bool m_isHoveredOver { false };
};