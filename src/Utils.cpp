#pragma once
#include "Utils.h"

void Utils::ChangeManualWindowResizing(bool value)
{
	HWND consoleWindow = GetConsoleWindow();
	if (value)
	{
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) | WS_MAXIMIZEBOX | WS_SIZEBOX);
	}
	else
	{
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	}
}

void Utils::ChangeWindowSize(int width, int height) 
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void Utils::ResetScreen(std::vector<IDrawable*>* drawables)
{
	ClearScreen();

	for (size_t i = 0; i < drawables->size(); i++)
	{
		(*drawables)[i]->Draw();
	}

	return;
}

void Utils::ClearScreen()
{
	//system("cls"); //For whatever reasons this disables any mouseinputs

	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);

	return;
}

void Utils::EnableFullscreen()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}

void Utils::EnableWindowedMode()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
}

void Utils::setForeGroundAndBackGroundColor(int foreGroundColor, int backGroundColor)
{
	int color = 16 * backGroundColor + foreGroundColor;
	SetColor(color);
}

void Utils::SetCursorPosition()
{
	COORD position{ 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Utils::SetCursorPosition(COORD* position)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *position);
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
}

void Utils::DrawPixel(COORD* position, unsigned char Color)
{
	SetColor(Color);
	SetCursorPosition(position);
	std::cout << m_Square;
}

void Utils::DrawPixel(int x, int y, unsigned char Color)
{
	SetColor(Color);
	COORD position{ x, y };
	SetCursorPosition(&position);
	std::cout << m_Square;
}

void Utils::DrawPixel(COORD* position, unsigned char Color, char character)
{
	SetColor(Color);
	SetCursorPosition(position);
	std::cout << character;
}

void Utils::DrawPixel(int x, int y, unsigned char Color, char character)
{
	SetColor(Color);
	COORD position{ x, y };
	SetCursorPosition(&position);
	std::cout << character;
}

void Utils::DrawCircle(COORD* position, int radius, int color)
{
	int x = position->X;
	int y = position->Y;

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

void Utils::DrawLine(COORD* position0, COORD* position1, int color)
{
	int x0 = position0->X;
	int y0 = position0->Y;
	int x1 = position1->X;
	int y1 = position1->Y;

	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; }
	else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; }
	else { stepx = 1; }
	dy <<= 1;                                                  // dy is now 2*dy
	dx <<= 1;                                                  // dx is now 2*dx

	DrawPixel(x0, y0, color);
	if (dx > dy) {
		int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                                // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;                                    // same as fraction -= 2*dy
			DrawPixel(x0, y0, color);
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
			DrawPixel(x0, y0, color);
		}
	}
}

void Utils::DrawBigX(COORD* position, int size, int color)
{
	if (!(size % 2)) size++; //Make sure size is uneven

	int leftX = position->X - size * 2 - 1;
	int rightX = position->X + size * 2;
	int topY = position->Y - size;
	int bottomY = position->Y + size;

	COORD leftTop{ leftX, topY };
	COORD leftBottom{ leftX, bottomY };
	COORD rightTop{ rightX, topY };
	COORD rightBottom{ rightX, bottomY };

	DrawLine(&leftTop, &rightBottom, color);
	DrawLine(&leftBottom, &rightTop, color);
}

void Utils::DrawFrameCenter(COORD* position, int width, int height, int color)
{
	if (!(width % 2)) width++; //Make sure width is uneven
	if (!(height % 2)) height++; //Make sure height is uneven

	int leftX = position->X - ((width - 1) / 2);
	int topY = position->Y - ((height - 1) / 2);
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

void Utils::DrawFrameTopLeft(COORD* position, int width, int height, int color, char character)
{
	int leftX = position->X;
	int topY = position->Y;
	int rightX = leftX + width;
	int bottomY = topY + height;

	{
		DrawPixel(leftX, topY, color, character); //Top left corner of drawframe
		DrawPixel(rightX, topY, color, character); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, color, character); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color, character); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, color, character); // Top horizontol line
			DrawPixel(i, bottomY, color, character); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, color, character); //Left Vertical line
			DrawPixel(rightX, i, color, character); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeftDoubleLined(COORD* position, int width, int height, int color)
{
	int leftX = position->X;
	int topY = position->Y;
	int rightX = leftX + width;
	int bottomY = topY + height;

	{
		DrawPixel(leftX, topY, color, m_DoubleLineCornerTopLeft); //Top left corner of drawframe
		DrawPixel(rightX, topY, color, m_DoubleLineCornerTopRight); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, color, m_DoubleLineCornerBottomLeft); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color, m_DoubleLineCornerBottomRight); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, color, m_DoubleLineHorizontal); // Top horizontol line
			DrawPixel(i, bottomY, color, m_DoubleLineHorizontal); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, color, m_DoubleLineVertical); //Left Vertical line
			DrawPixel(rightX, i, color, m_DoubleLineVertical); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeftSingleLined(COORD* position, int width, int height, int color)
{
	int leftX = position->X;
	int topY = position->Y;
	int rightX = leftX + width;
	int bottomY = topY + height;

	{
		DrawPixel(leftX, topY, color, m_SingleLineCornerTopLeft); //Top left corner of drawframe
		DrawPixel(rightX, topY, color, m_SingleLineCornerTopRight); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, color, m_SingleLineCornerBottomLeft); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, color, m_SingleLineCornerBottomRight); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, color, m_SingleLineHorizontal); // Top horizontol line
			DrawPixel(i, bottomY, color, m_SingleLineHorizontal); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, color, m_SingleLineVertical); //Left Vertical line
			DrawPixel(rightX, i, color, m_SingleLineVertical); //Right Vertical Line
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
			COORD drawPos{ i * 6, j };
			SetCursorPosition(&drawPos);
			std::cout << i << "," << j;
		}
		setForeGroundAndBackGroundColor(7, 0);
		COORD drawPos{ 0,17 };
		SetCursorPosition(&drawPos);
		std::cout << "Forgroundcolor, backgroundcolor";
	}
}

void Utils::DrawColorPalette(COORD* position)
{
	int x = position->X;
	int y = position->Y;

	for (int i = x; i < 16 + x; i++)
	{
		for (int j = y; j < 16 + y; j++)
		{
			setForeGroundAndBackGroundColor(i - x, j - y);
			COORD drawPos{ i * 6, j };
			SetCursorPosition(&drawPos);
			std::cout << i << "," << j;
		}
	}
	setForeGroundAndBackGroundColor(7, 0);
	COORD drawPos{ x, y + 17 };
	SetCursorPosition(&drawPos);
	std::cout << "Forgroundcolor, backgroundcolor";
}

void Utils::DrawCharPalette()
{
	SetCursorPosition();
	SetColor(15);
	for (int i = 0; i < 256; i++)
	{
		std::cout << (unsigned char)i << " " << i << "\n";
	}
}

void Utils::DrawCharPalette(COORD* position, int Color)
{
	SetCursorPosition(position);
	SetColor(Color);
	for (int i = 0; i < 256; i++)
	{
		std::cout << (unsigned char)i << " " << i << "\n";
	}
}

void Utils::DrawString(COORD* position, unsigned char color, const std::string text)
{
	SetColor(color);
	SetCursorPosition(position);
	std::cout << text;
}

void Utils::DrawString(COORD* position, unsigned char color, const std::vector<std::string>* text)
{
	for (int i = 0; i < text->size(); i++)
	{
		COORD newPos{ position->X, position->Y + i };
		DrawString(&newPos, color, (*text)[i]);
	}
}

void Utils::DrawWString(COORD* position, unsigned char color, const std::wstring text)
{
	int i = _setmode(_fileno(stdout), 0x20000);

	SetColor(color);
	SetCursorPosition(position);
	std::wcout << text;

	i = _setmode(_fileno(stdout), _O_TEXT);
}

void Utils::DrawWString(COORD* position, unsigned char color, const std::vector<std::wstring>* text)
{
	for (int i = 0; i < text->size(); i++)
	{
		COORD newPosition = *position;
		newPosition.Y += i;
		DrawWString(&newPosition, color, (*text)[i]);
	}
}