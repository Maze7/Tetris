#pragma once
#include <SFML/Graphics.hpp>

namespace TetrisGame {

	class Tetromino
	{

	public:
		typedef int TetroShape[4][4];

		enum TETROMINO_TYPE { I = 0, J = 1, L = 2, O = 3, S = 4, T = 5, Z = 6, END = 7 };

		enum MOVE_ACTION { RIGHT = 0, LEFT = 1, DOWN = 2, UP = 3 };

		enum ROTATION_ACTION { FORWARD = 0, BACKWARD = 1 };

		// Spawn position of a preview Tetromino
		static constexpr int PREVIEW_POS[2] = { 11, 1 };

		// Spawn position of a playable tetromino
		static constexpr int PLAYFIELD_POS[2] = { 3, 0 };

		// Contains all Shape definitions 
		static const TetroShape SHAPE_DATA[TETROMINO_TYPE::END][4];

		// Defines the amount of rotation that a tetromino type can perform
		static const int SHAPE_SIZE[TETROMINO_TYPE::END];
    
		// Defines the color for the corresponding shapes
		static const sf::Color SHAPE_COLORS[TETROMINO_TYPE::END];

	private:

		// Type of the tetromino
		TETROMINO_TYPE m_type;

		// Position of the tetromino
		sf::Vector2i m_position;

		// Current rotation
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
