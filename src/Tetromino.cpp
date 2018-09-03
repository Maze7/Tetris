#include "Tetromino.h"


const std::vector<TetroShape> Tetromino::vectorI =
{
	{   // oben
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 1 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
	},
	{   // rechts
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
	}
};

const std::vector<TetroShape> Tetromino::vectorJ =
{
	{	// oben
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{	// rechts
		{ 1, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{	// unten
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{	// links
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}
};

const std::vector<TetroShape> Tetromino::vectorL =
{
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 1, 0, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 }
	}
};

const std::vector<TetroShape> Tetromino::vectorO =
{
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	}
};

const std::vector<TetroShape> Tetromino::vectorS =
{
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
	},
	{
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
	}
};

const std::vector<TetroShape> Tetromino::vectorT =
{
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 1, 0, 0 }
	},
	{
		{ 0, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 0, 0 }
	}
};

const std::vector<TetroShape> Tetromino::vectorZ =
{
	{
		{ 0, 0, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 0, 0, 0 },
	},
	{
		{ 0, 0, 1, 0 },
		{ 0, 1, 1, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 0, 0 },
	}
};

const std::map<const Tetromino::TETROMINO_TYPE, const std::vector<TetroShape>*> Tetromino::s_TETRO_SHAPES = // https://stackoverflow.com/questions/138600/initializing-a-static-stdmapint-int-in-c
{
	{ Tetromino::J, &Tetromino::vectorJ },{Tetromino::I, &Tetromino::vectorI },
	{ Tetromino::L, &Tetromino::vectorL },{Tetromino::O, &Tetromino::vectorO },
	{ Tetromino::S, &Tetromino::vectorS },{Tetromino::T, &Tetromino::vectorT },
	{ Tetromino::Z, &Tetromino::vectorZ }
};


Tetromino::~Tetromino()
{
}



/*
	
	
*/
void Tetromino::rotate(ROTATION_ACTION action)
{
	std::vector<TetroShape> const* TetroShapeS = s_TETRO_SHAPES.at(m_type);

	switch(action) {
	case Tetromino::FORWARD:
		if (m_rotation < TetroShapeS->size() - 1)
			m_rotation++;
		else //if (m_rotation >= TetroShapeS->size() - 1) {
			m_rotation = 0;
		
		break;

	case Tetromino::BACKWARD:

		if (m_rotation == 0) 
			m_rotation = TetroShapeS[0].size() - 1;
		else 
			m_rotation--;

		break;
	}
}
