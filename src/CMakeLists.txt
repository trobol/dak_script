
file(GLOB_RECURSE SOURCE_FILES "./*.cpp")
list(REMOVE_ITEM SOURCE_FILES "main.cpp")

option(ADD_PROFILING "ADD_PROFILING" OFF)
    if(ADD_PROFILING)
    message(STATUS "profiling enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
endif()


# Make an automatic library - will be static or dynamic based on user setting
add_library(dak_script ${SOURCE_FILES})


# We need this directory, and users of our library will need it too
target_include_directories(dak_script PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_executable(compile "./main.cpp")
target_link_libraries(compile PRIVATE dak_script)


install(TARGETS compile DESTINATION bin)


# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})


add_custom_target(profile

    COMMAND ${CMAKE_INSTALL_PREFIX}/bin/compile ../example_file.txt
    COMMAND gprof ${CMAKE_INSTALL_PREFIX}/bin/compile gmon.out | gprof2dot | dot -Tpng -o output.png

    COMMENT "profiling compile"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

)