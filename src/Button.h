/*****************************************************************************
* Project: DrawingWorksV2
* File : Button.h
* Date : 09.09.2025
* Author : Bastian Pfaller (BP)
*
* A custom button class that can display a button in the console.
* The button can have diffrent visuals for it's hovered state.
* 
* 
* History:
* 09.09.25 BP Created
******************************************************************************/


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
	Button(COORD a_position, int a_width, int a_height, unsigned char a_buttonColor, unsigned char a_hoverColor, std::wstring a_buttonName);

	/// <summary>
	/// Draws the button
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// Handles the on click event
	/// </summary>
	void OnClicked();

	/// <summary>
	/// Handles if the hoverd state changes
	/// </summary>
	/// <param name="a_value"></param>
	void OnHoveredChanged(bool a_value);

	/// <summary>
	/// Checks if a coordinate is inside the button
	/// </summary>
	/// <param name="a_coord"></param>
	/// <returns></returns>
	bool PointInButton(COORD* a_coord);

	inline COORD* GetPosition() { return &m_position; }
	inline Event<>& GetOnButtonClickedEvent() { return m_onButtonClicked; }
	inline bool GetButtonHoverState() { return m_isHoveredOver; }

private:
	/// <summary>
	/// Actually draw the button
	/// </summary>
	/// <param name="a_color"></param>
	void ActualDraw(unsigned char a_color);

	COORD m_position{};
	int m_width{ 0 };
	int m_height{ 0 };
	unsigned char m_buttonColor{ 0 };
	unsigned char m_hoverColor{ 0 };

	COORD m_labelPosition{};
	std::wstring m_label{};

	Event<> m_onButtonClicked{};

	bool m_isHoveredOver { false };
};