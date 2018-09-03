#pragma once
#include <SFML/Graphics.hpp>
#include "Tetromino.h"


class Block : sf::RectangleShape
{

private:
	Tetromino::TETROMINO_TYPE m_type;
public:
	Block(Tetromino::TETROMINO_TYPE);
	~Block();

	sf::Color generateColor(); 
};
