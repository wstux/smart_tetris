find_package(Curses REQUIRED)

#if(CURSES_FOUND)
    add_custom_target(ncurses)
    set_target_properties(ncurses
                          PROPERTIES
                              LIBRARIES "${CURSES_LIBRARIES}"
    )
    set_target_properties(ncurses
                          PROPERTIES
                              INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIR}"
    )
#else()
#    message(INFO " boost not found")
#endif()

