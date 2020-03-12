# src: https://gitlab.com/CLIUtils/modern-cmake/-/blob/master/examples/extended-project/cmake/add_FetchContent_MakeAvailable.cmake
macro(FetchContent_MakeAvailable NAME)
    FetchContent_GetProperties(${NAME})
    if(NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
    endif()
endmacro()

