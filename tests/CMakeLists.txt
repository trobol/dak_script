# Testing library
FetchContent_Declare(
Catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)



file(GLOB_RECURSE SOURCE_FILES "*.cpp")


add_executable(dak_script_test ${SOURCE_FILES})

include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)
target_link_libraries(dak_script_test PRIVATE dak_script Catch2::Catch2)

catch_discover_tests(dak_script_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})