/*****************************************************************************
* Project: DrawingWorksV2
* File : LoadingScreen.h
* Date : 06.10.2025
* Author : Bastian Pfaller (BP)
*
* A simple loading screen displayed in the console.
*
* History:
* 06.10.25 BP Created
******************************************************************************/

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

	const int M_MAXFILLAMOUNT{ 100 };
	int m_currentFillAmount{ 0 };

	const COORD M_LOADINGBARSTART{2,1};

	Event<> m_onLoadingFinished{};

	unsigned char m_color{};
};

