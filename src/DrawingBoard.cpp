#include "DrawingBoard.h"


DrawingBoard::DrawingBoard()
{
	m_inputManager.EnableMouseInput(true);
	m_inputManager.EnableDrawing(true);

	m_inputManager.GetKeyInputEvent(VK_ESCAPE)	+= [this]() { ExitDrawing(); };
	m_inputManager.GetKeyInputEvent(VK_F1)		+= [this]() { DrawControls(); };
	m_inputManager.GetKeyInputEvent(VK_F2)		+= Utils::ClearScreen;
	m_inputManager.GetKeyInputEvent(VK_F3)		+= Utils::EnableFullscreen;
	m_inputManager.GetKeyInputEvent(VK_F4)		+= Utils::EnableWindowedMode;
}

void DrawingBoard::Load()
{
	m_hasUserExited = false;

	Utils::ChangeWindowSize(1500, 900);
	Utils::ChangeManualWindowResizing(true);

	Utils::ClearScreen();
	Utils::SetCursorPosition();
	std::cout << "Note: By pressing F1 you can view the controlls.";

	DrawingLoop();
}

void DrawingBoard::DrawingLoop()
{
	while (!m_hasUserExited)
	{
		m_inputManager.HandleInput();
	}
}

void DrawingBoard::DrawControls()
{
	COORD pos{ 0,0 };
	Utils::DrawWString(&pos, 9, ConsoleArtLibrary::DrawingControls());
}

void DrawingBoard::ExitDrawing()
{
	m_hasUserExited = true;
}