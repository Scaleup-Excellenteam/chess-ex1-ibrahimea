# Create the main Chess executable.
add_executable(Chess
		main.cpp
		Chess.cpp
		Piece.cpp
)

# Add the "include" directory to the compiler search path.
target_include_directories(Chess PRIVATE ${CMAKE_SOURCE_DIR}/include)
