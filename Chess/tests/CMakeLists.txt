cmake_minimum_required(VERSION 3.10)
project(ChessTests)
set(CMAKE_CXX_STANDARD 11)

# Tell CMake to include the "include" folder for headers.
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src   # if any headers reside here too
)

add_executable(test_move_validation test_move_validation.cpp)
target_sources(test_move_validation PRIVATE ../src/Pieces.cpp)

enable_testing()
add_test(NAME ValidateMoves COMMAND test_move_validation)
