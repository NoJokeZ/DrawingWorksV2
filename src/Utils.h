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
	static void ChangeManualWindowResizing(bool value);

	static void ChangeWindowSize(int width, int height);

	static void ClearScreen();

	static void ResetScreen(std::vector<IDrawable*>* drawables);

	static void EnableFullscreen();

	static void EnableWindowedMode();

	static void setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor);

	static void SetCursorPosition();

	static void SetCursorPosition(COORD* position);

	static void SetColor(WORD color);

	static void DrawPixel(COORD* position, unsigned char Color);

	static void DrawPixel(int x, int y, unsigned char Color);

	static void DrawPixel(COORD* position, unsigned char Color, char character);

	static void DrawPixel(int x, int y, unsigned char Color, char character);

	static void DrawCircle(COORD* position, int radius, int color);

	static void DrawLine(COORD* position0, COORD* position1, int color);

	static void DrawBigX(COORD* position, int size, int color);

	static void DrawFrameCenter(COORD* position, int width, int height, int color);

	static void DrawFrameTopLeft(COORD* position, int width, int height, int color, char charakter);

	static void DrawFrameTopLeftDoubleLined(COORD* position, int width, int height, int color);

	static void DrawFrameTopLeftSingleLined(COORD* position, int width, int height, int color);

	static void DrawColorPalette();

	static void DrawColorPalette(COORD* position);

	static void DrawCharPalette();

	static void DrawCharPalette(COORD* position, int Color);

	static void DrawString(COORD* position, unsigned char color, const std::string text);

	static void DrawString(COORD* position, unsigned char color, const std::vector<std::string>* text);

	static void DrawWString(COORD* position, unsigned char color, const std::wstring text);

	static void DrawWString(COORD* position, unsigned char color, const std::vector<std::wstring>* text);
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

