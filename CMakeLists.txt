cmake_minimum_required(VERSION 3.31)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
        src/MoveRecommendation.cpp
        src/Chess.cpp 
        src/Board.cpp
        src/Rook.cpp
        src/Bishop.cpp
        src/Knight.cpp
        src/Queen.cpp
        src/King.cpp
        src/Pawn.cpp
        src/main.cpp
)
add_executable(ChessEngine ${SOURCES})
