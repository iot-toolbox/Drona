cmake_minimum_required(VERSION 3.0)
project(dronaSrcLibCommunication)

# Search .cpp in ./src
file(GLOB_RECURSE sources Src/*.cpp)
file(GLOB_RECURSE includes Includes/*.h)

# Include path
INCLUDE_DIRECTORIES(includes)

# Build exectuable
add_library(communication STATIC ${sources} ${includes})

TARGET_LINK_LIBRARIES(communication pthread)
TARGET_LINK_LIBRARIES(communication logger)
