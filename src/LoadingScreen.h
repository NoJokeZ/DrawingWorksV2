#pragma once
#include <Windows.h>
#include "Event.h"


class LoadingScreen
{
public:
	inline Event<>& GetOnLoadingFinishedEvent() { return m_onLoadingFinished; }

	void StartLoading();

	void FinishedLoading();

private:

	void AddFill(int value);

	const int m_maxFillAmount{ 100 };
	int m_currentFillAmount{ 0 };

	const COORD m_loadingBarStart{2,1};

	Event<> m_onLoadingFinished{};

	unsigned char m_color{};

};

