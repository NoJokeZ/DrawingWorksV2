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
#include "Button.h"
#include "Input.h"

const std::vector<std::wstring> header{   LR"(                                                                                )",
										  LR"(╔══════════════════════════════════════════════════════════════════════════════╗)",
										  LR"(║                                                                              ║)",
										  LR"(║                   Simple Console Drawing Application                         ║)",
										  LR"(║                                                                              ║)",
										  LR"(╠══════════════════════════════════════════════════════════════════════════════╣)",
										  LR"(║ Controls:                                                                    ║)",
										  LR"(║                                                                              ║)",
										  LR"(║ LeftClick               ->     Draw white square/pixel                       ║)",
										  LR"(║ RightClick              ->     Draw random colored square/pixel              ║)",
										  LR"(║ LeftClick + LeftAlt     ->     Draw random colored circle                    ║)",
										  LR"(║ LeftClick + LeftCtrl    ->     Draw random colored X                         ║)",
										  LR"(║ LeftClick + Shift       ->     Draw random colored frame                     ║)",
										  LR"(║ Escape                  ->     Exit                                          ║)",
										  LR"(║                                                                              ║)",
										  LR"(║ F1                      ->     Fullscreen                                    ║)",
										  LR"(║ F2                      ->     Windowed                                      ║)",
										  LR"(║                                                                              ║)",
										  LR"(║ Debug:                                                                       ║)",
										  LR"(║ F5                      ->     Draw color palette                            ║)",
										  LR"(║ F6                      ->     Draw char palette                             ║)",
										  LR"(║                                                                              ║)",
										  LR"(╚══════════════════════════════════════════════════════════════════════════════╝)" };

const std::string clearButtonDescription = "<--- Reset console \n";
int buttonX = 1, buttonY = header.size() + 1;

HANDLE _outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE _inputHandle = GetStdHandle(STD_INPUT_HANDLE);
DWORD _consoleInputMode = (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;

CONSOLE_CURSOR_INFO _cci;

Button resetButton = Button(new RECT{buttonX, buttonY, buttonX + 20, buttonY + 4 }, L"<Reset Console>");

std::vector<Button*> buttons = { &resetButton };

bool isButtonPressed;

Input InputManager = Input(_inputHandle, buttons);

void HandleInput();
void resetscreen();

void logxy(COORD coord);
void logRect(RECT rect);

enum GameState
{
	Initializing, Running, Exit
};
GameState _gameState;

enum GameMode
{
	Drawing, TicTacToe
};

int main()
{
	_gameState = Initializing;

	resetButton.GetOnButtonClickedEvent() += resetscreen;

	////Key events
	//*InputManager.GetKeyInputEvent(VK_F1) += Utils::ChangeConsoleToFullScreen;
	//*InputManager.GetKeyInputEvent(VK_F1) += resetscreen;
	//*InputManager.GetKeyInputEvent(VK_F2) += Utils::ChangeConsoleToWindowed;
	//*InputManager.GetKeyInputEvent(VK_F2) += resetscreen;

	////Debug delete later
	//*InputManager.GetKeyInputEvent(VK_F5) += resetscreen;
	//*InputManager.GetKeyInputEvent(VK_F5) += []() {Utils::drawcolorpalette(); };
	//*InputManager.GetKeyInputEvent(VK_F6) += resetscreen;
	//*InputManager.GetKeyInputEvent(VK_F6) += []() {Utils::drawcharpalette(); };


	//Mouse events
	//*InputManager.GetMouseInputEvent(Input::MouseInputType::LeftClick) += 

	//Cursor settings
	_cci.dwSize = 25;
	_cci.bVisible = FALSE;
	SetConsoleCursorInfo(_outputHandle, &_cci);

	SetConsoleMode(_inputHandle, _consoleInputMode);

	//Initialize screen
	resetscreen();

	_gameState = Running;

	while (_gameState == Running)
	{
		//InputManager.HandleInput();

		HandleInput();
	}

	return 0;
}

void HandleInput()
{
	INPUT_RECORD inputRecord;
	DWORD events;
	COORD coord;
	POINT point;

	ReadConsoleInput(_inputHandle, &inputRecord, 1, &events);

	switch (inputRecord.EventType)
	{

	case MOUSE_EVENT:

		isButtonPressed = FALSE;

		coord.X = inputRecord.Event.MouseEvent.dwMousePosition.X;
		coord.Y = inputRecord.Event.MouseEvent.dwMousePosition.Y;

		point = { coord.X, coord.Y };

		//Button hover handling

		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (PtInRect(buttons[i]->GetRect(), point))
			{
				buttons[i]->OnHoveredChanged(true);
			}
			else if (!PtInRect(buttons[i]-> GetRect(), point) && buttons[i]-> GetButtonHoverState())
			{
				buttons[i]->OnHoveredChanged(false);
			}
		}

		//Button handling
		if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED || inputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			for (size_t i = 0; i < buttons.size(); i++)
			{
				if (PtInRect(buttons[i]-> GetRect(), point))
				{
					buttons[i]->OnClicked();
					isButtonPressed = TRUE;
					break;
				}
			}
		}

		if (isButtonPressed) break;

		if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_ALT_PRESSED)
		{
			Utils::DrawCircle(coord.X, coord.Y, 4, rand() % 7 + 9);
		}
		else if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && inputRecord.Event.MouseEvent.dwControlKeyState & SHIFT_PRESSED)
		{
			Utils::DrawFrameCenter(coord.X, coord.Y, 9, 5, rand() % 7 + 9);
		}
		else if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && inputRecord.Event.MouseEvent.dwControlKeyState & LEFT_CTRL_PRESSED)
		{
			Utils::DrawBigX(coord.X, coord.Y, 3, rand() % 7 + 9);
		}
		else if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			Utils::DrawPixel(coord.X, coord.Y, 15);
		}
		else if (inputRecord.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			Utils::DrawPixel(coord.X, coord.Y, rand() % 7 + 9);
		}

		break;
		//Screen resize event
	case WINDOW_BUFFER_SIZE_EVENT:
		resetscreen();
		break;
		//Window focus event
	case FOCUS_EVENT:
		break;
		//Window menu event
	case MENU_EVENT:
		break;
		//Unknown event
	default:
		std::cout << "Unknown event called \n";
		break;
	}

	FlushConsoleInputBuffer(_inputHandle);
}

void resetscreen()
{
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

	//Redraw controls
	Utils::DrawWString(0, 0, 15, header);

	////Redraw reset button
	//Utils::drawpixel(buttonX, buttonY, 15);
	//Utils::Drawtext(buttonX + 2, buttonY, 3, clearButtonDescription);

	resetButton.DrawMe();
	return;
}

void logxy(COORD coord)
{
	Utils::SetCursorPosition(0, 0);
	std::cout << "X:" << coord.X << "  ";
	Utils::SetCursorPosition(7, 0);
	std::cout << "Y:" << coord.Y << "  ";
}

void logRect(RECT rect)
{
	Utils::SetCursorPosition(20, 0);
	std::cout << "L:" << rect.left << "  ";
	Utils::SetCursorPosition(27, 0);
	std::cout << "T:" << rect.top << "  ";
	Utils::SetCursorPosition(34, 0);
	std::cout << "R:" << rect.right << "  ";
	Utils::SetCursorPosition(41, 0);
	std::cout << "B:" << rect.bottom << "  ";
}