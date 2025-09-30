#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>

static class Utils
{
public:
	static bool TryParse(std::string& input, int& output, std::string& errMsg);

	static void EnableFullscreen();

	static void EnableWindowedMode();

	static void setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor);

	static void SetCursorPosition(int x, int y);

	static void SetColor(WORD color);

	static void DrawPixel(int x, int y, unsigned char Color);

	static void DrawPixel(int x, int y, unsigned char Color, char character);

	static void DrawCircle(int x, int y, int radius, int color);

	static void DrawLine(int x0, int y0, int x1, int y1, int color);

	static void DrawBigX(int x, int y, int size, int color);

	static void DrawFrameCenter(int x, int y, int width, int height, int color);

	static void DrawFrameTopLeft(int x, int y, int width, int height, int color, char charakter);

	static void DrawFrameTopLeftDoubleLined(int x, int y, int width, int height, int color);

	static void DrawFrameTopLeftSingleLined(int x, int y, int width, int height, int color);

	static void DrawColorPalette();

	static void DrawColorPalette(int x, int y);

	static void DrawCharPalette();

	static void DrawCharPalette(int x, int y, int Color);

	static void DrawString(int x, int y, unsigned char color, const std::string text);

	static void DrawString(int x, int y, unsigned char color, const std::vector<std::string> text);

	static void DrawWString(int x, int y, unsigned char color, const std::wstring text);

	static void DrawWString(int x, int y, unsigned char color, const std::vector<std::wstring> text);
};

