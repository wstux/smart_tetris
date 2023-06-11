TestTarget(ut_core_test
    SOURCES
        ut_core_test.cpp
    LIBRARIES
        core
    DEPENDS
        testing
)

TestTarget(ut_shape_test
    SOURCES
        ut_shape_test.cpp
    LIBRARIES
        core
    DEPENDS
        testing
)

