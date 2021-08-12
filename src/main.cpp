#include <ctime>
#include"Tetramino.h"

const int FIELD_HEIGHT = 20;
const int FIELD_WIDTH  = 10;
int arrField[FIELD_HEIGHT][FIELD_WIDTH] = { 0 };

bool checkBoards(const Tetramino& figure)
{
	for (int segment = 0; segment < figure.GetSegments(); ++segment)
	{
		Tetramino::SegmentCord cord2d = figure.GetSegmCord(segment);
		if (cord2d.x < 0 || cord2d.x >= FIELD_WIDTH || 
			cord2d.y < 0 || cord2d.y >= FIELD_HEIGHT)
		{
			return false;
		}
		else if (arrField[cord2d.y][cord2d.x])
			return false;
	}
	return true;
}

int main()
{
	srand(time(0));	

	enum class Direction
	{
		NONE = 0,
		LEFT = -1,
		RIGHT = 1,
		ROTATE
	} e_direction;

	// Window
	sf::RenderWindow window(sf::VideoMode(576, 864), "Tetris");	
	window.setFramerateLimit(30);
	
	// Tetramino
	Tetramino figure;
	using Type = Tetramino::Type;
	using Color = Tetramino::Color;
	Type type = static_cast<Type>(rand() % (int)Type::MAX_TYPES);
	Color color = static_cast<Color>(rand() % (int)Color::MAX_COLORS + 1);
	figure.ChangeType(type);

	// Field
	sf::Texture txField = figure.GetTexture();
	sf::Texture txFieldBkgrnd;
	txFieldBkgrnd.loadFromFile("D:\\!Devasted\\PRO\\Tetris\\Images\\background.png");
	sf::Sprite spFieldBkgrnd;
	spFieldBkgrnd.setTexture(txFieldBkgrnd);
	sf::Texture txFieldFrame;
	txFieldFrame.loadFromFile("D:\\!Devasted\\PRO\\Tetris\\Images\\frame.png");
	sf::Sprite spFieldFrame;
	spFieldFrame.setTexture(txFieldFrame);
	sf::Sprite spField;
	spField.setTexture(txField);
	int fieldResl = figure.GetResolution();

	// Timer
	sf::Clock clock;
	float time = 0.0f;
	float timer = 0.0f;
	float delay = 0.0f;

	// Event
	sf::Event event;

	while (window.isOpen())
	{	
		// Event reset
		delay = 0.3f;
		time = clock.getElapsedTime().asSeconds();
		timer += time;
		clock.restart();
		e_direction = Direction::NONE;

		// Event check
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && checkBoards(figure))
			{
				if (event.key.code == sf::Keyboard::Up)
					e_direction = Direction::ROTATE;
				else if (event.key.code == sf::Keyboard::Left)
					e_direction = Direction::LEFT;
				else if (event.key.code == sf::Keyboard::Right)
					e_direction = Direction::RIGHT;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					delay = 0.05f;
			}
		}
		// Event execute 
		if (timer > delay)
		{			
			figure.MoveOY(1);
			if (!checkBoards(figure))
			{
				for (int segment = 0; segment < figure.GetSegments(); ++segment)
				{
					Tetramino::SegmentCord oldCord2d = figure.GetOldSegmCord(segment);
					arrField[oldCord2d.y][oldCord2d.x] = static_cast<int>(color);
				}
				// Spawn
				figure.ChangeType(type);
				if (checkBoards(figure))
				{
					type = static_cast<Type>(rand() % (int)Type::MAX_TYPES);
					color = static_cast<Color>(rand() % (int)Color::MAX_COLORS + 1);
					figure.ChangeType(type);
				}
			}
			timer = 0;
		}
		if (e_direction == Direction::ROTATE)
		{
			figure.RotateR();
			if (!checkBoards(figure))
				figure.UndoMoveOXnR();
		}
		else
		{
			figure.MoveOX((int)e_direction);
			if (!checkBoards(figure))
				figure.UndoMoveOXnR();
		}
		// Delete completed lines		
		int underRow = FIELD_HEIGHT - 1;
		for (int row = FIELD_HEIGHT - 1; row > 0; --row)
		{
			int occupiedCount = 0;
			for (int col = 0; col < FIELD_WIDTH; ++col)
			{
				if (arrField[row][col]) 
					++occupiedCount;
				arrField[underRow][col] = arrField[row][col];
			}
			if (occupiedCount < FIELD_WIDTH) 
				--underRow;
		}
		// Rendering
		window.clear(sf::Color::White);
		window.draw(spFieldBkgrnd);
		for (int row = 0; row < FIELD_HEIGHT; ++row)
		{
			for (int col = 0; col < FIELD_WIDTH; ++col)
			{
				if (arrField[row][col] == 0)
					continue;
				spField.setTextureRect(sf::IntRect(arrField[row][col] * fieldResl,
					0, fieldResl, fieldResl));
				spField.setPosition(col * fieldResl, row * fieldResl);
				spField.move(28, 31);
				window.draw(spField);
			}
		}
		figure.Drow(color, window, 28, 31);
		window.draw(spFieldFrame);
		window.display();
	}
	return 0;
}
