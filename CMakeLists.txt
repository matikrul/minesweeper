cmake_minimum_required(VERSION 3.28)

project(Minesweeper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_subdirectory(engine)
add_subdirectory(app)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()