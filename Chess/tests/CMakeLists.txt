cmake_minimum_required(VERSION 3.10)
project(ChessTests)
set(CMAKE_CXX_STANDARD 11)

# Tell CMake to include the "include" folder (and src if needed) for headers.
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

# Build the test executable.
add_executable(test_move_validation test_move_validation.cpp)

# Add Piece.cpp (which contains the implementation for Pieces.h) to the test target.
target_sources(test_move_validation PRIVATE ${CMAKE_SOURCE_DIR}/Chess/src/Piece.cpp)

enable_testing()
add_test(NAME ValidateMoves COMMAND test_move_validation)
