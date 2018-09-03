#pragma once
#include <SFML/Graphics.hpp>
#include "Typedefs.h"


class Tetromino
{

public:
	// END is used for black color
	enum TETROMINO_TYPE { I, J, L, O, S, T, Z, END };

	// 
	enum MOVE_ACTION { RIGHT, LEFT, DOWN };

	//
	enum ROTATION_ACTION { FORWARD, BACKWARD };

	//
	static constexpr int PREVIEW_POS[2] = { 1, 1 };
	static constexpr int PLAYFIELD_POS[2] = { 3, 0 };

private:
	static const std::vector<TetroShape> vectorI;
	static const std::vector<TetroShape> vectorJ;
	static const std::vector<TetroShape> vectorL;
	static const std::vector<TetroShape> vectorO;
	static const std::vector<TetroShape> vectorS;
	static const std::vector<TetroShape> vectorT;
	static const std::vector<TetroShape> vectorZ;

	TETROMINO_TYPE m_type;
	sf::Vector2i m_position;
	int m_rotation;

public:

	// TODO
	static const std::map<const TETROMINO_TYPE, const std::vector<TetroShape>*> s_TETRO_SHAPES;

	Tetromino(TETROMINO_TYPE& type, int position[2]) : m_type(type), m_position(position[0], position[1]), m_rotation(0) {};
	~Tetromino();
	

	void rotate(ROTATION_ACTION action);
	void move(MOVE_ACTION action);

};