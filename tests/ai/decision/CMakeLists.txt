add_executable(minesweeper_ai_decision_tests
    ActionDecoderTests.cpp
    ActionsPerCellTests.cpp
    MaxScoreStrategyTests.cpp
)

target_link_libraries(minesweeper_ai_decision_tests
    PRIVATE
        minesweeper_ai
        GTest::gtest_main
)

gtest_discover_tests(minesweeper_ai_decision_tests)
