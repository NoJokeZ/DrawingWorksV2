#pragma once
#include <iostream>
#include <vector>

static class ConsoleArtLibrary
{
public:
	static const std::vector<std::wstring>& MenuHeader();
	static const std::vector<std::wstring>& LoadingBarEmpty();
	static const std::vector<std::wstring>& DrawingControls();
	static const std::vector<std::wstring>& LoadingBarFillElement();
};
