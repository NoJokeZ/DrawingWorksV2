#include <chrono>
#include <thread>
#include "LoadingScreen.h"
#include "Utils.h"
#include "ConsoleArtLibrary.h"

void LoadingScreen::StartLoading()
{
	Utils::ClearScreen();
	Utils::ChangeWindowSize(870, 125);

	srand(time(0));
	m_color = rand() % 14 + 1;
	COORD pos{ 0,0 };

	Utils::DrawWString(&pos, m_color, ConsoleArtLibrary::LoadingBarEmpty());

	bool isLoadingFinished{ false };

	while (!isLoadingFinished)
	{
		int fillAmount = rand() % 4 + 1;
		AddFill(fillAmount);

		int sleepAmount = rand() % 10;
		//int sleepAmount = rand() % 400 + 100;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepAmount));

		if (m_currentFillAmount >= M_MAXFILLAMOUNT) isLoadingFinished = true;
	}

	FinishedLoading();
}

void LoadingScreen::FinishedLoading()
{
	m_onLoadingFinished.Invoke();
}


void LoadingScreen::AddFill(int a_value)
{
	if (m_currentFillAmount + a_value > M_MAXFILLAMOUNT)
	{
		a_value = M_MAXFILLAMOUNT - m_currentFillAmount;
	}

	for (int i = 0; i < a_value; i++)
	{
		COORD pos{ M_LOADINGBARSTART.X + m_currentFillAmount, M_LOADINGBARSTART.Y };

		Utils::DrawWString(&pos, m_color, ConsoleArtLibrary::LoadingBarFillElement());

		m_currentFillAmount++;
	}
}