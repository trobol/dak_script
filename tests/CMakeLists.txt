# Testing library
FetchContent_Declare(
catch2
GIT_REPOSITORY https://github.com/catchorg/Catch2.git
GIT_TAG        v2.9.1
)
FetchContent_MakeAvailable(catch2)
# Adds Catch2::Catch2


file(GLOB_RECURSE SOURCE_FILES "*.cpp")

# Tests need to be added as executables first
add_executable(dak_script_test ${SOURCE_FILES})

# I'm using C++17 in the test
target_compile_features(dak_script_test PRIVATE cxx_std_17)

# Should be linked to the main library, as well as the Catch2 testing library
target_link_libraries(dak_script_test PRIVATE dak_script Catch2::Catch2)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(dak_script dak_script_test) # Command can be a target
