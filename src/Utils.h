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
	static bool tryParse(std::string& input, int& output, std::string& errMsg);

	static void ChangeConsoleToFullScreen();

	static void ChangeConsoleToWindowed();

	static void setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor);

	static void gotoxy(int x, int y);

	static void setcolor(WORD color);

	static void drawpixel(int x, int y, unsigned char Color);

	static void drawpixel2(int x, int y, unsigned char Color, char character);

	static void drawcircle(int x, int y, int radius, int color);

	static void drawline(int x0, int y0, int x1, int y1, int color);

	static void drawbigX(int x, int y, int size, int color);

	static void drawframeMiddle(int x, int y, int width, int height, int color);

	static void drawframeTopLeft(int x, int y, int width, int height, int color, char charakter);

	static void drawframeTopLeftDoubleLined(int x, int y, int width, int height, int color);

	static void drawframeTopLeftSingleLined(int x, int y, int width, int height, int color);

	static void drawcolorpalette();

	static void drawcolorpalette(int x, int y);

	static void drawcharpalette();

	static void drawcharpalette(int x, int y, int Color);

	static void Drawtext(int x, int y, unsigned char color, const std::string text);

	static void Drawtext(int x, int y, unsigned char color, const std::vector<std::string> text);

	static void DrawWtext(int x, int y, unsigned char color, const std::wstring text);

	static void DrawWtext(int x, int y, unsigned char color, const std::vector<std::wstring> text);
};

