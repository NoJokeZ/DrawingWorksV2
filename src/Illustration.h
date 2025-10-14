#pragma once
#include <iostream>
#include <vector>
#include "IDrawable.h"
#include "Utils.h"

class Illustration : public IDrawable
{
public:
	Illustration(COORD position, unsigned char color, std::vector<std::wstring>* illustration);
	virtual void Draw();
	void ChangeColor(unsigned char color);
private:
	COORD m_position{};
	unsigned char m_color{};
	std::vector<std::wstring>* m_illustration{ nullptr };
};

