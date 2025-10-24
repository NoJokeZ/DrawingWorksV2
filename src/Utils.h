#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "IDrawable.h"

static class Utils
{
public:
	static void ChangeManualWindowResizing(bool a_value);

	static void ChangeWindowSize(int a_width, int a_height);

	static void ClearScreen();

	static void ResetScreen(std::vector<IDrawable*>* a_drawables);

	static void EnableFullscreen();

	static void EnableWindowedMode();

	static void setForeGroundAndBackGroundColor(int a_foreGroundColor, int a_backGroundColor);

	static void SetCursorPosition();

	static void SetCursorPosition(COORD* a_position);

	static void SetColor(WORD a_color);

	static void DrawPixel(COORD* a_position, unsigned char a_color);

	static void DrawPixel(int a_x, int a_y, unsigned char a_color);

	static void DrawPixel(COORD* a_position, unsigned char a_color, char a_character);

	static void DrawPixel(int a_x, int a_y, unsigned char a_color, char a_character);

	static void DrawCircle(COORD* a_position, int a_radius, int a_color);

	static void DrawLine(COORD* a_position0, COORD* a_position1, int a_color);

	static void DrawBigX(COORD* a_position, int a_size, int a_color);

	static void DrawFrameCenter(COORD* a_position, int a_width, int a_height, int a_color);

	static void DrawFrameTopLeft(COORD* a_position, int a_width, int a_height, int a_color, char a_charakter);

	static void DrawFrameTopLeftDoubleLined(COORD* a_position, int a_width, int a_height, int a_color);

	static void DrawFrameTopLeftSingleLined(COORD* a_position, int a_width, int a_height, int a_color);

	static void DrawColorPalette();

	static void DrawColorPalette(COORD* a_position);

	static void DrawCharPalette();

	static void DrawCharPalette(COORD* a_position, int a_color);

	static void DrawString(COORD* a_position, unsigned char a_color, const std::string a_text);

	static void DrawString(COORD* a_position, unsigned char a_color, const std::vector<std::string>* a_text);

	static void DrawWString(COORD* a_position, unsigned char a_color, const std::wstring a_text);

	static void DrawWString(COORD* a_position, unsigned char a_color, const std::vector<std::wstring>* a_text);
private:
	static const unsigned char m_Square = (unsigned char)219;
	static const unsigned char m_SquareLight = (unsigned char)176;

	static const unsigned char m_DoubleLineCornerTopLeft = (unsigned char)201;
	static const unsigned char m_DoubleLineCornerTopRight = (unsigned char)187;
	static const unsigned char m_DoubleLineCornerBottomLeft = (unsigned char)200;
	static const unsigned char m_DoubleLineCornerBottomRight = (unsigned char)188;
	static const unsigned char m_DoubleLineHorizontal = (unsigned char)205;
	static const unsigned char m_DoubleLineVertical = (unsigned char)186;

	static const unsigned char m_SingleLineCornerTopLeft = (unsigned char)218;
	static const unsigned char m_SingleLineCornerTopRight = (unsigned char)191;
	static const unsigned char m_SingleLineCornerBottomLeft = (unsigned char)192;
	static const unsigned char m_SingleLineCornerBottomRight = (unsigned char)217;
	static const unsigned char m_SingleLineHorizontal = (unsigned char)196;
	static const unsigned char m_SingleLineVertical = (unsigned char)179;

};

