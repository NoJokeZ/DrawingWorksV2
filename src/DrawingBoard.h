#pragma once
#include "Input.h"
#include "Utils.h"
#include "ConsoleArtLibrary.h"

class DrawingBoard
{
public:
	DrawingBoard();
	void Load();

private:
	void DrawingLoop();
	void DrawControls();
	void ExitDrawing();

	Input m_inputManager{};

	bool m_hasUserExited{ false };
};

