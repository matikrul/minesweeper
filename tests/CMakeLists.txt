add_executable(minesweeper_tests
    BoardTests.cpp
)

target_link_libraries(minesweeper_tests
    PRIVATE
        minesweeper_engine
        GTest::gtest_main
)

add_test(NAME minesweeper_tests COMMAND minesweeper_tests)