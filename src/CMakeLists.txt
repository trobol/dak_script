
file(GLOB_RECURSE SOURCE_FILES "./*.cpp")
list(REMOVE_ITEM SOURCE_FILES "main.cpp")



# Make an automatic library - will be static or dynamic based on user setting
add_library(dak_script ${SOURCE_FILES})


# We need this directory, and users of our library will need it too
target_include_directories(dak_script PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_executable(compile "./main.cpp")
target_link_libraries(compile PRIVATE dak_script)

# IDEs should put the headers in a nice place
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})