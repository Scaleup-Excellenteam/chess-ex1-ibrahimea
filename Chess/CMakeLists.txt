cmake_minimum_required(VERSION 3.15)
project(Chess)

# Set the C++ standard.
if (MSVC AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
    set(CMAKE_CXX_STANDARD 23)
else()
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive- /Zc:externConstexpr /Zc:inline)
endif()

# Add the src and tests subdirectories.
add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(tests)
