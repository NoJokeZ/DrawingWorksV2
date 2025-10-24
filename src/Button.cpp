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


Button::Button(COORD a_position, int a_width, int a_height, unsigned char a_buttonColor, unsigned char a_hoverColor, std::wstring a_buttonName)
{
	m_position = a_position;
	m_width = a_width;
	m_height = a_height;
	m_buttonColor = a_buttonColor;
	m_hoverColor = a_hoverColor;


	m_label = a_buttonName;


	m_labelPosition.X = (m_position.X + (m_width / 2)) - (a_buttonName.length() / 2);
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

void Button::OnHoveredChanged(bool a_value)
{
	if (m_isHoveredOver == a_value) return;

	m_isHoveredOver = a_value;

	if (m_isHoveredOver)
	{
		ActualDraw(m_hoverColor);
	}
	else
	{
		ActualDraw(m_buttonColor);
	}
}

bool Button::PointInButton(COORD* a_coord)
{
	if (a_coord->X < m_position.X || a_coord->X >(m_position.X + m_width)) return false;
	if (a_coord->Y < m_position.Y || a_coord->Y >(m_position.Y + m_height)) return false;
	return true;
}

void Button::ActualDraw(unsigned char a_color)
{
	Utils::DrawFrameTopLeftDoubleLined(&m_position, m_width, m_height, a_color);
	Utils::DrawWString(&m_labelPosition, a_color, m_label);
}
