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
	RECT Rect;

	Event<> OnButtonClicked;

	bool IsHoveredOver;

	Button(RECT rect, std::wstring buttonName);

	void DrawMe();

	void OnClicked();

	void OnHoveredChanged(bool value);

private:
	int m_iNameX;
	int m_iNameY;
	std::wstring m_sButtonName;
};

