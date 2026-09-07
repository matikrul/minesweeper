add_library(minesweeper_engine
    src/Board.cpp
    src/BoardView.cpp
    src/Cell.cpp
    src/Game.cpp
)

target_include_directories(minesweeper_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(minesweeper_engine
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        $<$<CXX_COMPILER_ID:MSVC>:/WX>
        $<$<CXX_COMPILER_ID:MSVC>:/permissive->
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wextra>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wpedantic>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wconversion>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wsign-conversion>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wshadow>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror>
)