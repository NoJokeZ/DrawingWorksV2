#pragma once
#include "Utils.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>

const char square = (unsigned char)219;

const char squareLight = (unsigned char)176;

const char doubleLineCornerTopLeft = (unsigned char)201;
const char doubleLineCornerTopRight = (unsigned char)187;
const char doubleLineCornerBottomLeft = (unsigned char)200;
const char doubleLineCornerBottomRight = (unsigned char)188;
const char doubleLineHorizontal = (unsigned char)205;
const char doubleLineVertical = (unsigned char)186;

const char singleLineCornerTopLeft = (unsigned char)218;
const char singleLineCornerTopRight = (unsigned char)191;
const char singleLineCornerBottomLeft = (unsigned char)192;
const char singleLineCornerBottomRight = (unsigned char)217;
const char singleLineHorizontal = (unsigned char)196;
const char singleLineVertical = (unsigned char)179;

bool Utils::TryParse(std::string& input, int& output, std::string& errMsg)
{
	try
	{
		errMsg = "";
		output = std::stoi(input);
	}
	catch (std::invalid_argument)
	{
		errMsg = "Input was not a number.";
		return false;
	}
	catch (std::out_of_range)
	{
		errMsg = "Number was to big.";
		return false;
	}
	return true;
}

void Utils::EnableFullscreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void Utils::EnableWindowedMode()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
}

void Utils::setForeGroundAndBackGroundColor(int ForeGroundColor, int BackGroundColor)
{
	int color = 16 * BackGroundColor + ForeGroundColor;
	SetColor(color);
}

void Utils::SetCursorPosition(int x, int y)
{
	COORD coord = { x,y };
	//coord.X = x; coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

#pragma region Colors
//     0 = Black
//     1 = Blue
//     2 = Green
//     3 = Cyan
//     4 = Red
//     5 = Magenta
//     6 = Yellow
//     7 = LightGray
//     8 = DarkGray
//     9 = LightBlue
//     10 = LightGreen
//     11 = LightCyan
//     12 = LightRed
//     13 = LightMagenta
//     14 = LightYellow
//     15 = White
#pragma endregion

void Utils::SetColor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void Utils::DrawPixel(int x, int y, unsigned char Color)
{
	SetColor(Color);
	SetCursorPosition(x, y);
	std::cout << square;
}

void Utils::DrawPixel(int x, int y, unsigned char Color, char character)
{
	SetColor(Color);
	SetCursorPosition(x, y);
	std::cout << character;
}

void Utils::DrawCircle(int x, int y, int radius, int color)
{
	int actualWitdthRadius = radius * 2 - 1;

	int wx, wy;
	int thresh;
	int actualWitdthRadiusSqrd = actualWitdthRadius * actualWitdthRadius;
	int radiusSqrd = radius * radius;
	int xa, ya;

	DrawPixel(x, y + radius, color);
	DrawPixel(x, y - radius, color);

	wx = 0;
	wy = radius;
	xa = 0;
	ya = actualWitdthRadiusSqrd * 2 * radius;
	thresh = actualWitdthRadiusSqrd / 4 - actualWitdthRadiusSqrd * radius;

	for (;;) {
		thresh += xa + radiusSqrd;

		if (thresh >= 0) {
			ya -= actualWitdthRadiusSqrd * 2;
			thresh -= ya;
			wy--;
		}

		xa += radiusSqrd * 2;
		wx++;

		if (xa >= ya)
			break;


		DrawPixel(x + wx, y - wy, color);
		DrawPixel(x - wx, y - wy, color);
		DrawPixel(x + wx, y + wy, color);
		DrawPixel(x - wx, y + wy, color);
	}

	DrawPixel(x + actualWitdthRadius, y, color);
	DrawPixel(x - actualWitdthRadius, y, color);

	wx = actualWitdthRadius;
	wy = 0;
	xa = radiusSqrd * 2 * actualWitdthRadius;

	ya = 0;
	thresh = radiusSqrd / 4 - radiusSqrd * actualWitdthRadius;

	for (;;) {
		thresh += ya + actualWitdthRadiusSqrd;

		if (thresh >= 0) {
			xa -= radiusSqrd * 2;
			thresh = thresh - xa;
			wx--;
		}

		ya += actualWitdthRadiusSqrd * 2;
		wy++;

		if (ya > xa)
			break;

		DrawPixel(x + wx, y - wy, color);
		DrawPixel(x - wx, y - wy, color);
		DrawPixel(x + wx, y + wy, color);
		DrawPixel(x - wx, y + wy, color);
	}
}

void Utils::DrawLine(int x0, int y0, int x1, int y1, int color)
{
	int pix = color;
	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; }
	else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; }
	else { stepx = 1; }
	dy <<= 1;                                                  // dy is now 2*dy
	dx <<= 1;                                                  // dx is now 2*dx

	DrawPixel(x0, y0, pix);
	if (dx > dy) {
		int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                                // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;                                    // same as fraction -= 2*dy
			DrawPixel(x0, y0, pix);
		}
	}
	else {
		int fraction = dx - (dy >> 1);
		while (y0 != y1) {
			if (fraction >= 0) {
				x0 += stepx;
				fraction -= dy;
			}
			y0 += stepy;
			fraction += dx;
			DrawPixel(x0, y0, pix);
		}
	}
}

void Utils::DrawBigX(int x, int y, int size, int color)
{
	if (!(size % 2)) size++; //Make sure size is uneven

	int leftX = x - size * 2 - 1;
	int rightX = x + size * 2;
	int topY = y - size;
	int bottomY = y + size;

	DrawLine(leftX, topY, rightX, bottomY, color);
	DrawLine(leftX, bottomY, rightX, topY, color);
}

void Utils::DrawFrameCenter(int x, int y, int width, int height, int color)
{
	if (!(width % 2)) width++; //Make sure width is uneven
	if (!(height % 2)) height++; //Make sure height is uneven

	int leftX = x - ((width - 1) / 2);
	int topY = y - ((height - 1) / 2);
	int rightX = leftX + width;
	int bottomY = topY + height;

	{
		DrawPixel(leftX, topY, color); //Top left corner of drawframe
		DrawPixel(rightX, topY, color); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, color); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, color); // Top horizontol line
			DrawPixel(i, bottomY, color); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, color); //Left Vertical line
			DrawPixel(rightX, i, color); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeft(int x, int y, int width, int height, int color, char character)
{
	int rightX = x + width;
	int bottomY = y + height;

	{
		DrawPixel(x, y, color, character); //Top left corner of drawframe
		DrawPixel(rightX, y, color, character); //Top right corner of drawframe
		DrawPixel(x, bottomY, color, character); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color, character); //Bottom right corner of drawframe

		for (int i = x + 1; i < rightX; i++)
		{
			DrawPixel(i, y, color, character); // Top horizontol line
			DrawPixel(i, bottomY, color, character); // Bottom Horizontal line
		}

		for (int i = y + 1; i < bottomY; i++)
		{
			DrawPixel(x, i, color, character); //Left Vertical line
			DrawPixel(rightX, i, color, character); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeftDoubleLined(int x, int y, int width, int height, int color)
{
	int rightX = x + width;
	int bottomY = y + height;

	{
		DrawPixel(x, y, color, doubleLineCornerTopLeft); //Top left corner of drawframe
		DrawPixel(rightX, y, color, doubleLineCornerTopRight); //Top right corner of drawframe
		DrawPixel(x, bottomY, color, doubleLineCornerBottomLeft); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color, doubleLineCornerBottomRight); //Bottom right corner of drawframe

		for (int i = x + 1; i < rightX; i++)
		{
			DrawPixel(i, y, color, doubleLineHorizontal); // Top horizontol line
			DrawPixel(i, bottomY, color, doubleLineHorizontal); // Bottom Horizontal line
		}

		for (int i = y + 1; i < bottomY; i++)
		{
			DrawPixel(x, i, color, doubleLineVertical); //Left Vertical line
			DrawPixel(rightX, i, color, doubleLineVertical); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeftSingleLined(int x, int y, int width, int height, int color)
{
	int rightX = x + width;
	int bottomY = y + height;

	{
		DrawPixel(x, y, color, singleLineCornerTopLeft); //Top left corner of drawframe
		DrawPixel(rightX, y, color, singleLineCornerTopRight); //Top right corner of drawframe
		DrawPixel(x, bottomY, color, singleLineCornerBottomLeft); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color, singleLineCornerBottomRight); //Bottom right corner of drawframe

		for (int i = x + 1; i < rightX; i++)
		{
			DrawPixel(i, y, color, singleLineHorizontal); // Top horizontol line
			DrawPixel(i, bottomY, color, singleLineHorizontal); // Bottom Horizontal line
		}

		for (int i = y + 1; i < bottomY; i++)
		{
			DrawPixel(x, i, color, singleLineVertical); //Left Vertical line
			DrawPixel(rightX, i, color, singleLineVertical); //Right Vertical Line
		}
	}
}

void Utils::DrawColorPalette()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			setForeGroundAndBackGroundColor(i, j);
			SetCursorPosition(i * 6, j); 
			std::cout << i << "," << j;
		}
		setForeGroundAndBackGroundColor(7, 0);
		SetCursorPosition(0, 17);
		std::cout << "Forgroundcolor, backgroundcolor";
	}
}

void Utils::DrawColorPalette(int x, int y)
{
	for (int i = x; i < 16 + x; i++)
	{
		for (int j = y; j < 16 + y; j++)
		{
			setForeGroundAndBackGroundColor(i - x, j - y);
			SetCursorPosition(i * 6, j);
			std::cout << i << "," << j;
		}
	}
	setForeGroundAndBackGroundColor(7, 0);
	SetCursorPosition(x, y + 17);
	std::cout << "Forgroundcolor, backgroundcolor";
}

void Utils::DrawCharPalette()
{
	SetCursorPosition(0, 0);
	SetColor(15);
	for (int i = 0; i < 256; i++)
	{
		std::cout << (unsigned char)i << " " << i << "\n";
	}
}

void Utils::DrawCharPalette(int x, int y, int Color)
{
	SetCursorPosition(x, y);
	SetColor(Color);
	for (int i = 0; i < 256; i++)
	{
		std::cout << (unsigned char)i << " " << i << "\n";
	}
}

void Utils::DrawString(int x, int y, unsigned char color, const std::string text)
{
	SetColor(color);
	SetCursorPosition(x, y);
	std::cout << text;
}

void Utils::DrawString(int x, int y, unsigned char color, const std::vector<std::string> text)
{
	for (int i = 0; i < text.size(); i++)
	{
		DrawString(x, y + i, color, text[i]);
	}
}

void Utils::DrawWString(int x, int y, unsigned char color, const std::wstring text)
{
	int i = _setmode(_fileno(stdout), 0x20000);

	SetColor(color);
	SetCursorPosition(x, y);
	std::wcout << text;

	i = _setmode(_fileno(stdout), _O_TEXT);
}

void Utils::DrawWString(int x, int y, unsigned char color, const std::vector<std::wstring> text)
{
	for (int i = 0; i < text.size(); i++)
	{
		DrawWString(x, y + i, color, text[i]);
	}
}