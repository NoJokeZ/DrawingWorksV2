#include "Illustration.h"

Illustration::Illustration(COORD position, unsigned char color, std::vector<std::wstring>* illustration)
{
	m_position = position;
	m_color = color;
	m_illustration = illustration;
}

void Illustration::Draw()
{
	Utils::DrawWString(&m_position, m_color, m_illustration);
}

void Illustration::ChangeColor(unsigned char color)
{
	m_color = color;
}