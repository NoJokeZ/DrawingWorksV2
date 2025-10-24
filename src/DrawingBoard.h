#pragma once
#include "Input.h"
#include "Utils.h"
#include "ConsoleArtLibrary.h"

class DrawingBoard
{
public:
	DrawingBoard();
	~DrawingBoard();
	void Load();

private:
	void DrawingLoop();
	void DrawControls();
	void ExitDrawing();

	Input* m_inputManager = new Input();

	bool m_hasUserExited{ false };
};

