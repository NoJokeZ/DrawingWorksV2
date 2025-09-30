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


Button::Button(RECT* rect, std::wstring buttonName)
{
	m_rect = rect;
	m_label = buttonName;

	m_labelX = (m_rect->right + m_rect->left) / 2 - (buttonName.length() / 2);
	m_labelY = (m_rect->bottom + m_rect->top) / 2;
}

void Button::DrawMe()
{
	Utils::DrawFrameTopLeftDoubleLined(m_rect->left, m_rect->top, m_rect->right - m_rect->left, m_rect->bottom - m_rect->top, 15);
	Utils::DrawWString(m_labelX, m_labelY, 15, m_label);
}

void Button::OnClicked()
{
	m_onButtonClicked.Invoke();
	m_isHoveredOver = false;
}

void Button::OnHoveredChanged(bool value)
{
	if (m_isHoveredOver == value) return;

	m_isHoveredOver = value;

	if (m_isHoveredOver)
	{
		Utils::DrawFrameTopLeftSingleLined(m_rect->left, m_rect->top, m_rect->right - m_rect->left, m_rect->bottom - m_rect->top, 9);
		Utils::DrawWString(m_labelX, m_labelY, 9, m_label);
	}
	else
	{
		DrawMe();
	}
}