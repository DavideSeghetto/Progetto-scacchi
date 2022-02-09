cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "-O2")

project(Scacchi)

add_library(scacchiera_library
	
	src/ChessBoard.cpp
	lib/ChessBoard.h
	src/position.cpp
	lib/position.h

	src/bishop.cpp
	lib/bishop.h
	src/king.cpp
	lib/king.h
	src/knight.cpp
	lib/knight.h
	src/pawn.cpp
	lib/pawn.h
	src/piece.cpp
	lib/piece.h
	src/queen.cpp
	lib/queen.h
	src/rook.cpp
	lib/rook.h

	lib/InvalidPosition.h
	lib/InvalidPiece.h
)

add_executable(scacchiera
	src/main.cpp
) 

target_link_libraries(scacchiera
	scacchiera_library
)

add_library(replay_library
	src/boardSimplified.cpp
	lib/boardSimplified.h
)

add_executable(replay
	src/replay.cpp
)

target_link_libraries(replay
	replay_library
)
