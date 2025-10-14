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


Button::Button(COORD position, int width, int height, unsigned char buttonColor, unsigned char hoverColor, std::wstring buttonName)
{
	m_position = position;
	m_width = width;
	m_height = height;
	m_buttonColor = buttonColor;
	m_hoverColor = hoverColor;


	m_label = buttonName;


	m_labelPosition.X = (m_position.X + (m_width / 2)) - (buttonName.length() / 2);
	m_labelPosition.Y = (m_position.Y + (m_height / 2));
}

void Button::Draw()
{
	ActualDraw(m_buttonColor);
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
		ActualDraw(m_hoverColor);
	}
	else
	{
		ActualDraw(m_buttonColor);
	}
}

bool Button::PointInButton(COORD* coord)
{
	if (coord->X < m_position.X || coord->X >(m_position.X + m_width)) return false;
	if (coord->Y < m_position.Y || coord->Y >(m_position.Y + m_height)) return false;
	return true;
}

void Button::ActualDraw(unsigned char color)
{
	Utils::DrawFrameTopLeftDoubleLined(&m_position, m_width, m_height, color);
	Utils::DrawWString(&m_labelPosition, color, m_label);
}
