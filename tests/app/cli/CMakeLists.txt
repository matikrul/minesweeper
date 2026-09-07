add_executable(minesweeper_cli_tests
    BoardPrinterTests.cpp
    ../../../app/cli/BoardPrinter.cpp
)

target_include_directories(minesweeper_cli_tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../../../app/cli
)

target_link_libraries(minesweeper_cli_tests
    PRIVATE
        minesweeper_engine
        GTest::gtest_main
)

gtest_discover_tests(minesweeper_cli_tests)
