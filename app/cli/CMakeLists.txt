add_executable(minesweeper_cli
    main.cpp
)

target_link_libraries(minesweeper_cli
    PRIVATE
        minesweeper_engine
)