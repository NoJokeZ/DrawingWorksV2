#pragma once
#include "Input.h"
#include "Utils.h"
#include "ConsoleArtLibrary.h"

class DrawingBoard
{
public:
	DrawingBoard();
	~DrawingBoard();

	/// <summary>
	/// Loads the drawing board
	/// </summary>
	void Load();

private:
	/// <summary>
	/// Activates the drawing loop
	/// </summary>
	void DrawingLoop();

	/// <summary>
	/// Draws the controls into the console
	/// </summary>
	void DrawControls();

	/// <summary>
	/// Exits the drawing board
	/// </summary>
	void ExitDrawing();

	Input* m_inputManager = new Input();

	bool m_hasUserExited{ false };
};

