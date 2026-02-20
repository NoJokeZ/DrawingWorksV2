#pragma once
#include "Utils.h"

void Utils::ChangeManualWindowResizing(bool a_value)
{
	HWND consoleWindow = GetConsoleWindow();
	if (a_value)
	{
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) | WS_MAXIMIZEBOX | WS_SIZEBOX);
	}
	else
	{
		SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	}
}

void Utils::ChangeWindowSize(int a_width, int a_height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, a_width, a_height, TRUE);
}

void Utils::ResetScreen(std::vector<IDrawable*>* a_drawables)
{
	ClearScreen();

	for (size_t i = 0; i < a_drawables->size(); i++)
	{
		(*a_drawables)[i]->Draw();
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

void Utils::SetForeGroundAndBackGroundColor(int a_foreGroundColor, int a_backGroundColor)
{
	int color = 16 * a_backGroundColor + a_foreGroundColor;
	SetColor(color);
}

void Utils::SetCursorPosition()
{
	COORD position{ 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void Utils::SetCursorPosition(COORD* a_position)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *a_position);
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

void Utils::SetColor(WORD a_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a_color);
}

void Utils::DrawPixel(COORD* a_position, unsigned char a_color)
{
	SetColor(a_color);
	SetCursorPosition(a_position);
	std::cout << M_SQUARE;
}

void Utils::DrawPixel(int a_x, int a_y, unsigned char a_color)
{
	SetColor(a_color);
	COORD position{ a_x, a_y };
	SetCursorPosition(&position);
	std::cout << M_SQUARE;
}

void Utils::DrawPixel(COORD* a_position, unsigned char a_color, char a_character)
{
	SetColor(a_color);
	SetCursorPosition(a_position);
	std::cout << a_character;
}

void Utils::DrawPixel(int a_x, int a_y, unsigned char a_color, char a_character)
{
	SetColor(a_color);
	COORD position{ a_x, a_y };
	SetCursorPosition(&position);
	std::cout << a_character;
}

void Utils::DrawCircle(COORD* a_position, int a_radius, int a_color)
{
	int x = a_position->X;
	int y = a_position->Y;

	int actualWitdthRadius = a_radius * 2 - 1;

	int wx, wy;
	int thresh;
	int actualWitdthRadiusSqrd = actualWitdthRadius * actualWitdthRadius;
	int radiusSqrd = a_radius * a_radius;
	int xa, ya;

	DrawPixel(x, y + a_radius, a_color);
	DrawPixel(x, y - a_radius, a_color);

	wx = 0;
	wy = a_radius;
	xa = 0;
	ya = actualWitdthRadiusSqrd * 2 * a_radius;
	thresh = actualWitdthRadiusSqrd / 4 - actualWitdthRadiusSqrd * a_radius;

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


		DrawPixel(x + wx, y - wy, a_color);
		DrawPixel(x - wx, y - wy, a_color);
		DrawPixel(x + wx, y + wy, a_color);
		DrawPixel(x - wx, y + wy, a_color);
	}

	DrawPixel(x + actualWitdthRadius, y, a_color);
	DrawPixel(x - actualWitdthRadius, y, a_color);

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

		DrawPixel(x + wx, y - wy, a_color);
		DrawPixel(x - wx, y - wy, a_color);
		DrawPixel(x + wx, y + wy, a_color);
		DrawPixel(x - wx, y + wy, a_color);
	}
}

void Utils::DrawLine(COORD* a_position0, COORD* a_position1, int a_color)
{
	int x0 = a_position0->X;
	int y0 = a_position0->Y;
	int x1 = a_position1->X;
	int y1 = a_position1->Y;

	int dy = y1 - y0;
	int dx = x1 - x0;
	int stepx, stepy;

	if (dy < 0) { dy = -dy;  stepy = -1; }
	else { stepy = 1; }
	if (dx < 0) { dx = -dx;  stepx = -1; }
	else { stepx = 1; }
	dy <<= 1;                                                  // dy is now 2*dy
	dx <<= 1;                                                  // dx is now 2*dx

	DrawPixel(x0, y0, a_color);
	if (dx > dy) {
		int fraction = dy - (dx >> 1);                         // same as 2*dy - dx
		while (x0 != x1) {
			if (fraction >= 0) {
				y0 += stepy;
				fraction -= dx;                                // same as fraction -= 2*dx
			}
			x0 += stepx;
			fraction += dy;                                    // same as fraction -= 2*dy
			DrawPixel(x0, y0, a_color);
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
			DrawPixel(x0, y0, a_color);
		}
	}
}

void Utils::DrawBigX(COORD* a_position, int a_size, int a_color)
{
	if (!(a_size % 2)) a_size++; //Make sure size is uneven

	int leftX = a_position->X - a_size * 2 - 1;
	int rightX = a_position->X + a_size * 2;
	int topY = a_position->Y - a_size;
	int bottomY = a_position->Y + a_size;

	COORD leftTop{ leftX, topY };
	COORD leftBottom{ leftX, bottomY };
	COORD rightTop{ rightX, topY };
	COORD rightBottom{ rightX, bottomY };

	DrawLine(&leftTop, &rightBottom, a_color);
	DrawLine(&leftBottom, &rightTop, a_color);
}

void Utils::DrawFrameCenter(COORD* a_position, int a_width, int a_height, int a_color)
{
	if (!(a_width % 2)) a_width++; //Make sure width is uneven
	if (!(a_height % 2)) a_height++; //Make sure height is uneven

	int leftX = a_position->X - ((a_width - 1) / 2);
	int topY = a_position->Y - ((a_height - 1) / 2);
	int rightX = leftX + a_width;
	int bottomY = topY + a_height;

	{
		DrawPixel(leftX, topY, a_color); //Top left corner of drawframe
		DrawPixel(rightX, topY, a_color); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, a_color); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, a_color); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, a_color); // Top horizontol line
			DrawPixel(i, bottomY, a_color); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, a_color); //Left Vertical line
			DrawPixel(rightX, i, a_color); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeft(COORD* a_position, int a_width, int a_height, int a_color, char a_character)
{
	int leftX = a_position->X;
	int topY = a_position->Y;
	int rightX = leftX + a_width;
	int bottomY = topY + a_height;

	{
		DrawPixel(leftX, topY, a_color, a_character); //Top left corner of drawframe
		DrawPixel(rightX, topY, a_color, a_character); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, a_color, a_character); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, a_color, a_character); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, a_color, a_character); // Top horizontol line
			DrawPixel(i, bottomY, a_color, a_character); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, a_color, a_character); //Left Vertical line
			DrawPixel(rightX, i, a_color, a_character); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeftDoubleLined(COORD* a_position, int a_width, int a_height, int a_color)
{
	int leftX = a_position->X;
	int topY = a_position->Y;
	int rightX = leftX + a_width;
	int bottomY = topY + a_height;

	{
		DrawPixel(leftX, topY, a_color, M_DOUBLELINECORNERTOPLEFT); //Top left corner of drawframe
		DrawPixel(rightX, topY, a_color, M_DOUBLELINECORNERTOPRIGHT); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, a_color, M_DOUBLELINECORNERBOTTOMLEFT); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, a_color, M_DOUBLELINECORNERBOTTOMRIGHT); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, a_color, M_DOUBLELINEHORIZONTAL); // Top horizontol line
			DrawPixel(i, bottomY, a_color, M_DOUBLELINEHORIZONTAL); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, a_color, M_DOUBLELINEVERTICAL); //Left Vertical line
			DrawPixel(rightX, i, a_color, M_DOUBLELINEVERTICAL); //Right Vertical Line
		}
	}
}

void Utils::DrawFrameTopLeftSingleLined(COORD* a_position, int a_width, int a_height, int a_color)
{
	int leftX = a_position->X;
	int topY = a_position->Y;
	int rightX = leftX + a_width;
	int bottomY = topY + a_height;

	{
		DrawPixel(leftX, topY, a_color, M_SINGLELINECORNERTOPLEFT); //Top left corner of drawframe
		DrawPixel(rightX, topY, a_color, M_SINGLELINECORNERTOPRIGHT); //Top right corner of drawframe
		DrawPixel(leftX, bottomY, a_color, M_SINGLELINECORNERBOTTOMLEFT); //Bottom left corner of drawframe
		DrawPixel(rightX, bottomY, a_color, M_SINGLELINECORNERBOTTOMRIGHT); //Bottom right corner of drawframe

		for (int i = leftX + 1; i < rightX; i++)
		{
			DrawPixel(i, topY, a_color, M_SINGLELINEHORIZONTAL); // Top horizontol line
			DrawPixel(i, bottomY, a_color, M_SINGLELINEHORIZONTAL); // Bottom Horizontal line
		}

		for (int i = topY + 1; i < bottomY; i++)
		{
			DrawPixel(leftX, i, a_color, M_SINGLELINEVERTICAL); //Left Vertical line
			DrawPixel(rightX, i, a_color, M_SINGLELINEVERTICAL); //Right Vertical Line
		}
	}
}

void Utils::DrawColorPalette()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			SetForeGroundAndBackGroundColor(i, j);
			COORD drawPos{ i * 6, j };
			SetCursorPosition(&drawPos);
			std::cout << i << "," << j;
		}
		SetForeGroundAndBackGroundColor(7, 0);
		COORD drawPos{ 0,17 };
		SetCursorPosition(&drawPos);
		std::cout << "Forgroundcolor, backgroundcolor";
	}
}

void Utils::DrawColorPalette(COORD* a_position)
{
	int x = a_position->X;
	int y = a_position->Y;

	for (int i = x; i < 16 + x; i++)
	{
		for (int j = y; j < 16 + y; j++)
		{
			SetForeGroundAndBackGroundColor(i - x, j - y);
			COORD drawPos{ i * 6, j };
			SetCursorPosition(&drawPos);
			std::cout << i << "," << j;
		}
	}
	SetForeGroundAndBackGroundColor(7, 0);
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

void Utils::DrawCharPalette(COORD* a_position, int a_color)
{
	SetCursorPosition(a_position);
	SetColor(a_color);
	for (int i = 0; i < 256; i++)
	{
		std::cout << (unsigned char)i << " " << i << "\n";
	}
}

void Utils::DrawString(COORD* a_position, unsigned char a_color, const std::string a_text)
{
	SetColor(a_color);
	SetCursorPosition(a_position);
	std::cout << a_text;
}

void Utils::DrawString(COORD* a_position, unsigned char a_color, const std::vector<std::string>* a_text)
{
	for (int i = 0; i < a_text->size(); i++)
	{
		COORD newPos{ a_position->X, a_position->Y + i };
		DrawString(&newPos, a_color, (*a_text)[i]);
	}
}

void Utils::DrawWString(COORD* a_position, unsigned char a_color, const std::wstring a_text)
{
	int i = _setmode(_fileno(stdout), 0x20000);

	SetColor(a_color);
	SetCursorPosition(a_position);
	std::wcout << a_text;

	i = _setmode(_fileno(stdout), _O_TEXT);
}

void Utils::DrawWString(COORD* a_position, unsigned char a_color, const std::vector<std::wstring>* a_text)
{
	for (int i = 0; i < a_text->size(); i++)
	{
		COORD newPosition = *a_position;
		newPosition.Y += i;
		DrawWString(&newPosition, a_color, (*a_text)[i]);
	}
}