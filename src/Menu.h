#pragma once
#include "Button.h"
#include "Input.h"
#include "Illustration.h"
#include "ConsoleArtLibrary.h"
#include "DrawingBoard.h"

class Menu
{
public:

	void Initialize();
	void Load();


private:
	void MenuLoop();

	void LoadDrawingBoard();
	
	void LoadCalculator();
	void LoadHelp();
	void LoadCredits();
	void Exit();

	DrawingBoard m_drawingBoard{};

	Button m_drawingBoardButton { new COORD{13, 9}, 20, 4, L"<Drawing Board>" };
	Button m_calculatorButton	{ new COORD{37, 9}, 20, 4, L"<Calculator>" };
	Button m_helpButton			{ new COORD{61, 9}, 20, 4, L"<Help>" };
	Button m_creditsButton		{ new COORD{25, 15}, 20, 4, L"<Credits>" };
	Button m_exitButton			{ new COORD{49, 15}, 20, 4, L"<Exit>" };

	std::vector<Button*> m_buttons{ &m_drawingBoardButton, &m_calculatorButton, &m_helpButton, &m_creditsButton, &m_exitButton };
	
	Illustration m_menuHeader{ new COORD{ 0,0 }, 15, ConsoleArtLibrary::MenuHeader() };

	Input m_inputManager{m_buttons};

	bool m_hasUserSelected{ false };
	bool m_hasUserExited{ false };


	void DrawMenu();
};

