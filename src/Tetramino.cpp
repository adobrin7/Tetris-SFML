#include "Tetramino.h"

Tetramino::Tetramino(void)
	: 
	m_nResolution(18),
	e_type(Type::NONE)
{
	m_texture.loadFromFile("D:\\!Devasted\\PRO\\Tetris\\Images\\tiles.png");
	m_sprite.setTexture(m_texture);
}

void Tetramino::Drow(const Color& color, sf::RenderWindow& window,
	int offsetOY, int offsetOX)
{
	if (e_type == Type::NONE)
		return;
	m_sprite.setTextureRect(sf::IntRect((int)color * m_nResolution,
		0, m_nResolution, m_nResolution));
	for (int segment = 0; segment < m_nSegments; ++segment)
	{
		m_sprite.setPosition(m_cord2d[segment].x * m_nResolution,
			m_cord2d[segment].y * m_nResolution);
		m_sprite.move(offsetOY, offsetOX);
		window.draw(m_sprite);
	}
}

void Tetramino::MoveOY(int step)
{
	for (int segment = 0; segment < m_nSegments; ++segment)
	{
		m_oldCord2d[segment].y = m_cord2d[segment].y;
		m_cord2d[segment].y += step;
	}
}

void Tetramino::MoveOX(int step)
{
	for (int segment = 0; segment < m_nSegments; ++segment)
	{
		m_oldCord2d[segment].x = m_cord2d[segment].x;
		m_cord2d[segment].x += step;
	}
}

void Tetramino::RotateR(void)
{
	SegmentCord rotationCenter = m_cord2d[1];
	for (int segment = 0; segment < m_nSegments; ++segment)
	{
		int dX = m_cord2d[segment].y - rotationCenter.y;
		int dY = m_cord2d[segment].x - rotationCenter.x;
		m_cord2d[segment].x = rotationCenter.x - dX;
		m_cord2d[segment].y = rotationCenter.y + dY;
	}
}

void Tetramino::UndoMoveOXnR(void)
{
	for (int segment = 0; segment < m_nSegments; ++segment)
	{
		m_cord2d[segment].x = m_oldCord2d[segment].x;
		m_cord2d[segment].y = m_oldCord2d[segment].y + 1; // avoid jerking up
	}
}

void Tetramino::RepresentIn2d(void)
{
	for (int segment = 0; segment < m_nSegments; ++segment)
	{
		m_cord2d[segment].x = m_arrTypes[(int)e_type][segment] % 2;
		m_cord2d[segment].y = m_arrTypes[(int)e_type][segment] / 2;
		m_oldCord2d[segment].x = m_cord2d[segment].x;
		m_oldCord2d[segment].y = m_cord2d[segment].y;
	}
}
