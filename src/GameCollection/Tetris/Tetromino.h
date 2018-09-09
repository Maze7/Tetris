#pragma once
#include <SFML/Graphics.hpp>
#include "Typedefs.h"

namespace TetrisGame {

	class Tetromino
	{

	public:
		typedef int TetroShape[4][4];

		// END is used for black color
		enum TETROMINO_TYPE { I = 0, J = 1, L = 2, O = 3, S = 4, T = 5, Z = 6, END = 7 };

		// 
		enum MOVE_ACTION { RIGHT = 0, LEFT = 1, DOWN = 2, UP = 3 };

		//
		enum ROTATION_ACTION { FORWARD = 0, BACKWARD = 1 };

		//
		static constexpr int PREVIEW_POS[2] = { 11, 1 };
		static constexpr int PLAYFIELD_POS[2] = { 3, 0 };

		// TODO
		static const TetroShape SHAPE_DATA[TETROMINO_TYPE::END][4];

		// TODO 
		static const int SHAPE_SIZE[TETROMINO_TYPE::END];
    
		//
		static const sf::Color SHAPE_COLORS[TETROMINO_TYPE::END];

	private:

		TETROMINO_TYPE m_type;
		sf::Vector2i m_position;
		int m_rotation;

	public:
   

		Tetromino(TETROMINO_TYPE type, const int position[2]) : m_type(type), m_position(position[0], position[1]), m_rotation(0) {};
		~Tetromino();

		const TETROMINO_TYPE& getType();
		const sf::Vector2i& getPosition();
		const int& getRotation();


		void rotate(ROTATION_ACTION action);
		void move(MOVE_ACTION action);

	};
}
