#include "Menu.h"
#include "LoadingScreen.h"

Menu::~Menu()
{
	delete m_drawingBoard;
	m_drawingBoard = nullptr;

	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		delete m_buttons[i];
	}

	delete m_menuHeader;
	m_menuHeader = nullptr;

	delete m_inputManager;
	m_inputManager = nullptr;
}

void Menu::Initialize()
{
	//Input
	m_inputManager->EnableMouseInput(true);
	
	//Button events
	m_drawingBoardButton->GetOnButtonClickedEvent()	+= [this]() { LoadDrawingBoard(); };
	m_calculatorButton->GetOnButtonClickedEvent()	+= [this]() { LoadCalculator(); };
	m_helpButton->GetOnButtonClickedEvent()			+= [this]() { LoadHelp(); };
	m_creditsButton->GetOnButtonClickedEvent()		+= [this]() { LoadCredits(); };
	m_exitButton->GetOnButtonClickedEvent()			+= [this]() { Exit(); };

	Load();

	MenuLoop();
}

void Menu::Load()
{
	//Disable manual window resizing
	Utils::ChangeManualWindowResizing(false);
	Utils::ChangeWindowSize(790, 370);

	//Change header to a random color between 1 and 14 / 0 is black and 15 is white (boring)
	srand(time(0));
	m_menuHeader->ChangeColor(rand() % 13 + 1);

	DrawMenu();
}

void Menu::MenuLoop()
{
	while (!m_hasUserExited)
	{
		m_inputManager->HandleInput();

		if (m_hasUserSelected)
		{
			m_hasUserSelected = false;
			Load();
		}
	}
}

void Menu::LoadDrawingBoard()
{
	m_hasUserSelected = true;

	LoadingScreen loadingScreen{};
	loadingScreen.GetOnLoadingFinishedEvent() += [this]() { m_drawingBoard->Load(); };

	loadingScreen.StartLoading();
}

void Menu::LoadCalculator()
{
	m_hasUserSelected = true;
}

void Menu::LoadHelp()
{
	m_hasUserSelected = true;
}

void Menu::LoadCredits()
{
	m_hasUserSelected = true;
}

void Menu::Exit()
{
	m_hasUserExited = true;
}

void Menu::DrawMenu()
{
	std::vector<IDrawable*> drawables;

	drawables.push_back(m_menuHeader);

	for (size_t i = 0; i < m_buttons.size(); i++)
	{
		drawables.push_back((m_buttons)[i]);
	}

	Utils::ResetScreen(&drawables);
}