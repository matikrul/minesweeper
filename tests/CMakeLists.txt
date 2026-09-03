include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    minesweeper_tests
    BoardTests.cpp
    BoardPrinterTests.cpp
    BoardViewTests.cpp
    CellTests.cpp
    GameTests.cpp
)

target_link_libraries(
    minesweeper_tests
    PRIVATE
    minesweeper_engine
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(minesweeper_tests)