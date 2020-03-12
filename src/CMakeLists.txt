
file(GLOB_RECURSE SOURCE_FILES "./*.cpp")

add_library(dak-script ${SOURCE_FILES})



include_directories(../include)