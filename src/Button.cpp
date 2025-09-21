#include "Button.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <functional>


Button::Button(RECT rect, std::wstring buttonName)
{
	Rect = rect;
	m_sButtonName = buttonName;

	m_iNameX = (rect.right + rect.left) / 2 - (buttonName.length() / 2);
	m_iNameY = (rect.bottom + rect.top) / 2;

	IsHoveredOver = false;
}

void Button::DrawMe()
{
	Utils::drawframeTopLeftDoubleLined(Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 15);
	Utils::DrawWtext(m_iNameX, m_iNameY, 15, m_sButtonName);
}

void Button::OnClicked()
{
	OnButtonClicked.Invoke();
	IsHoveredOver = false;
}

void Button::OnHoveredChanged(bool value)
{
	if (IsHoveredOver == value) return;

	IsHoveredOver = value;

	if (IsHoveredOver)
	{
		Utils::drawframeTopLeftSingleLined(Rect.left, Rect.top, Rect.right - Rect.left, Rect.bottom - Rect.top, 9);
		Utils::DrawWtext(m_iNameX, m_iNameY, 9, m_sButtonName);
	}
	else
	{
		DrawMe();
	}
}