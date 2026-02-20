/*****************************************************************************
* Project: DrawingWorksV2
* File : DrawingBoard.h
* Date : 06.10.2025
* Author : Bastian Pfaller (BP)
*
* This class functions like a canvas where the user can draw on.
* It includes diffrent keybinds to draw the display of the controls or
* change settings of the console window.
*
* History:
* 06.10.25 BP Created
******************************************************************************/


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

