#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Tetramino
{
public:
	Tetramino(void);

	enum class Type
	{
		I, Z, S, T, L, J, O, MAX_TYPES, NONE
	};
	enum class Color
	{
		BLUE,
		PURPLE,
		RED,
		GREEN,
		YELLOW,
		BRIGHT_BLUE,
		ORANGE,
		MAX_COLORS
	};
	struct SegmentCord
	{
		int x;
		int y;
	};

	int GetSegments(void) const { return m_nSegments; }
	int GetResolution(void) const { return m_nResolution; }
	sf::Texture GetTexture(void) const { return m_texture; }
	const SegmentCord& GetSegmCord(int segment) const
	{
		if (segment < 0 || segment > 4)
			throw -1;
		return m_cord2d[segment];
	}
	const SegmentCord& GetOldSegmCord(int segment) const
	{
		if (segment < 0 || segment > 4)
			throw - 1;
		return m_oldCord2d[segment];
	}

	void ChangeType(Type type) 
	{ 
		e_type = type; 
		RepresentIn2d();
	}
	void Drow(const Color& color, sf::RenderWindow& window,
		int offsetOY, int offsetOX);

	void MoveOY(int step);
	void MoveOX(int step);
	void RotateR(void);
	void UndoMoveOXnR(void);

private:
	void RepresentIn2d(void);	

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	const int m_nResolution;

	Type e_type;
	static const int m_nTypes = 7;
	static const int m_nSegments = 4;
	int m_arrTypes[m_nTypes][m_nSegments] =
	{
		1,3,5,7, // I
		2,4,5,7, // Z
		3,5,4,6, // S
		3,5,4,7, // T
		2,3,5,7, // L
		3,5,7,6, // J
		2,3,4,5, // O
	};

	SegmentCord m_cord2d[m_nSegments] = {0};
	SegmentCord m_oldCord2d[m_nSegments] = {0};
};
