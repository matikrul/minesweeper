add_library(minesweeper_engine
    src/Board.cpp
    src/BoardView.cpp
    src/Cell.cpp
    src/Game.cpp
    src/BoardPrinter.cpp
)

target_include_directories(minesweeper_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)