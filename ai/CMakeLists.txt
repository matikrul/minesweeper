add_library(minesweeper_ai
    src/decision/ActionDecoder.cpp
    src/encoding/BoardEncoder.cpp
)

target_include_directories(minesweeper_ai
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(minesweeper_ai
    PUBLIC
        minesweeper_engine
)

target_compile_options(minesweeper_ai
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