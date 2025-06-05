cmake_minimum_required(VERSION 3.31)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Point CMake at the “include” directory so it can find Chess.h, Board.h, etc.
include_directories(${CMAKE_SOURCE_DIR}/include)

# List all your .cpp files, including Chess.cpp
set(SOURCES
        src/MoveRecommendation.cpp
        src/Chess.cpp    # ← Add this line (path may differ if you placed Chess.cpp elsewhere)
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
