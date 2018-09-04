#pragma once
#include <SFML/Graphics.hpp>
#include "Typedefs.h"

namespace TetrisGame {

	class Tetromino
	{

	public:
		// END is used for black color
		enum TETROMINO_TYPE { I = 0, J = 1, L = 2, O = 3, S = 4, T = 5, Z = 6, END = 7 };

		// 
		enum MOVE_ACTION { RIGHT = 0, LEFT = 1, DOWN = 2 };

		//
		enum ROTATION_ACTION { FORWARD = 0, BACKWARD = 1 };

		//
		static constexpr int PREVIEW_POS[2] = { 1, 1 };
		static constexpr int PLAYFIELD_POS[2] = { 3, 0 };

	private:

		TETROMINO_TYPE m_type;
		sf::Vector2i m_position;
		int m_rotation;

	public:

		// TODO
		static const TetroShape SHAPE_DATA[TETROMINO_TYPE::END][4];

		Tetromino(TETROMINO_TYPE& type, int position[2]) : m_type(type), m_position(position[0], position[1]), m_rotation(0) {};
		~Tetromino();


		void rotate(ROTATION_ACTION action);
		void move(MOVE_ACTION action);

	};

}