/*****************************************************************************
* Project: DrawingWorksV2
* File : ConsoleArtLibrary.h
* Date : 05.10.2025
* Author : Bastian Pfaller (BP)
*
* A library for console illustrations.
*
* History:
* 05.10.25 BP Created
******************************************************************************/

#pragma once
#include <iostream>
#include <vector>

static class ConsoleArtLibrary
{
public:
	static std::vector<std::wstring>* MenuHeader();
	static std::vector<std::wstring>* LoadingBarEmpty();
	static std::vector<std::wstring>* DrawingControls();
	static std::vector<std::wstring>* LoadingBarFillElement();
	static std::vector<std::wstring>* Credits();
};
