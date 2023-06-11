ExecTarget(tetris_cli
    HEADERS
        details/console_tetris.h
    SOURCES
        main.cpp
        details/console_tetris.cpp
    LIBRARIES
        core
    DEPENDS
        ncurses
)

