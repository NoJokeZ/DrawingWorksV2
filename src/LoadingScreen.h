#pragma once
#include <Windows.h>
#include "Event.h"


class LoadingScreen
{
public:
	/// <summary>
	/// Starts the loading progress
	/// </summary>
	void StartLoading();

	/// <summary>
	/// Finalizes the loading process
	/// </summary>
	void FinishedLoading();

	inline Event<>& GetOnLoadingFinishedEvent() { return m_onLoadingFinished; }
private:

	void AddFill(int a_value);

	const int m_maxFillAmount{ 100 };
	int m_currentFillAmount{ 0 };

	const COORD m_loadingBarStart{2,1};

	Event<> m_onLoadingFinished{};

	unsigned char m_color{};
};

