#pragma once
#include <iostream>
#include <vector>
#include "IDrawable.h"
#include "Utils.h"

class Illustration : public IDrawable
{
public:
	Illustration(COORD a_position, unsigned char a_color, std::vector<std::wstring>* a_illustration);

	/// <summary>
	/// Draws the illustration
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// Changes the color of the illustration
	/// </summary>
	/// <param name="a_color"></param>
	void ChangeColor(unsigned char a_color);

private:
	COORD m_position{};
	unsigned char m_color{};
	std::vector<std::wstring>* m_illustration{ nullptr };
};

