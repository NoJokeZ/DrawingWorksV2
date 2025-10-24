#pragma once
#include "Button.h"
#include "Input.h"
#include "Illustration.h"
#include "ConsoleArtLibrary.h"
#include "DrawingBoard.h"

class Menu
{
public:
	~Menu();

	void Initialize();
	void Load();


private:
	void MenuLoop();

	void LoadDrawingBoard();
	
	void LoadCalculator();
	void LoadHelp();
	void LoadCredits();
	void Exit();

	void DrawMenu();

	DrawingBoard* m_drawingBoard = new DrawingBoard{};

	Button* m_drawingBoardButton = new Button(COORD{13, 9}, 20, 4, 15, 9, L"<Drawing Board>" );
	Button* m_calculatorButton = new Button(COORD{37, 9}, 20, 4, 15, 9,  L"<Calculator>");
	Button* m_helpButton = new Button(COORD{61, 9}, 20, 4, 15, 9,  L"<Help>");
	Button* m_creditsButton = new Button(COORD{25, 15}, 20, 4, 15, 9,  L"<Credits>");
	Button* m_exitButton = new Button(COORD{49, 15}, 20, 4, 15, 9,  L"<Exit>");

	std::vector<Button*> m_buttons { m_drawingBoardButton, m_calculatorButton, m_helpButton, m_creditsButton, m_exitButton };
	
	Illustration* m_menuHeader = new Illustration(COORD{ 0,0 }, 15, ConsoleArtLibrary::MenuHeader() );

	Input* m_inputManager = new Input(m_buttons);

	bool m_hasUserSelected{ false };
	bool m_hasUserExited{ false };

};

