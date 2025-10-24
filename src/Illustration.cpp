#include "Illustration.h"

Illustration::Illustration(COORD a_position, unsigned char a_color, std::vector<std::wstring>* a_illustration)
{
	m_position = a_position;
	m_color = a_color;
	m_illustration = a_illustration;
}

void Illustration::Draw()
{
	Utils::DrawWString(&m_position, m_color, m_illustration);
}

void Illustration::ChangeColor(unsigned char a_color)
{
	m_color = a_color;
}