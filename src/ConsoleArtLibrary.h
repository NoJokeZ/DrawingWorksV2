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
