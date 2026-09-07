add_executable(minesweeper_ai_encoding_tests
    BoardEncoderTests.cpp
)

target_link_libraries(minesweeper_ai_encoding_tests
    PRIVATE
        minesweeper_ai
        GTest::gtest_main
)

gtest_discover_tests(minesweeper_ai_encoding_tests)
