AUTOMAKE_OPTIONS = foreign
AM_CPPFLAGS = -std=c++11
AM_LDFLAGS = $(shell pkg-config sfml-all --libs)
bin_PROGRAMS = GameCollection
GameCollection_SOURCES = src/Exceptions/FileExceptions.h\
						src/FileIO/FileIO.cpp\
						src/FileIO/FileIO.h\
						src/FileIO/FileIO.o\
						src/Utility/Converter.cpp\
						src/Utility/Converter.h\
						src/Utility/Encryption.cpp\
						src/Utility/Encryption.h\
						src/GameCollection/Collection.cpp\
						src/GameCollection/Collection.h\
						src/GameCollection/GameCollection.cpp\
						src/GameCollection/ICollectionScreen.h\
						src/GameCollection/Menu/MainMenuScreen.cpp\
						src/GameCollection/Menu/MainMenuScreen.h\
						src/GameCollection/Tetris/GameScreen.cpp\
						src/GameCollection/Tetris/GameScreen.h\
						src/GameCollection/Tetris/Playfield.cpp\
						src/GameCollection/Tetris/Playfield.h\
						src/GameCollection/Tetris/SettingsScreen.cpp\
						src/GameCollection/Tetris/SettingsScreen.h\
						src/GameCollection/Tetris/TetrisLoader.cpp\
						src/GameCollection/Tetris/TetrisLoader.h\
						src/GameCollection/Tetris/MenuScreen.cpp\
						src/GameCollection/Tetris/MenuScreen.h\
						src/GameCollection/Tetris/ScoreScreen.h\
						src/GameCollection/Tetris/ScoreScreen.cpp\
						src/GameCollection/Tetris/TetrisScore.cpp\
						src/GameCollection/Tetris/TetrisScore.h\
						src/GameCollection/Tetris/Tetromino.cpp\
						src/GameCollection/Tetris/Tetromino.h\
						src/GameCollection/Tetris/Typedefs.h
