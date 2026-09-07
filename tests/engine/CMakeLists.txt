add_executable(
    minesweeper_engine_tests

    BoardTests.cpp
    BoardViewTests.cpp
    CellTests.cpp
    GameTests.cpp
)

target_include_directories(
    minesweeper_engine_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../engine/src
)

target_link_libraries(
    minesweeper_engine_tests
    PRIVATE
        minesweeper_engine
        GTest::gtest_main
)

gtest_discover_tests(minesweeper_engine_tests)