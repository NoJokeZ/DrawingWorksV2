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

	/// <summary>
	/// Initializes the menu
	/// </summary>
	void Initialize();

	/// <summary>
	/// Loads the menu
	/// </summary>
	void Load();


private:
	/// <summary>
	/// Starts the menu loop
	/// </summary>
	void MenuLoop();

	/// <summary>
	/// Loads into the drawing board
	/// </summary>
	void LoadDrawingBoard();
	
	/// <summary>
	/// Exits the application
	/// </summary>
	void Exit();

	/// <summary>
	/// Draws the menu into the console
	/// </summary>
	void DrawMenu();

	DrawingBoard* m_drawingBoard = new DrawingBoard{};

	Button* m_drawingBoardButton = new Button(COORD{10, 9}, 30, 4, 15, 9, L"<Drawing Board>" );
	Button* m_exitButton		 = new Button(COORD{52, 9}, 30, 4, 15, 9, L"<Exit>");

	std::vector<Button*> m_buttons { m_drawingBoardButton, m_exitButton };
	
	Illustration* m_menuHeader = new Illustration(COORD{ 0,0 }, 15, ConsoleArtLibrary::MenuHeader() );

	Input* m_inputManager = new Input(m_buttons);

	bool m_hasUserSelected{ false };
	bool m_hasUserExited{ false };

};

