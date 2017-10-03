cmake_minimum_required(VERSION 3.2.1)
project(hso)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# One warning from when compiling Eigen headers
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

include_directories("eigen3.3/include/eigen3/")

set(SRC hso.cpp)
set(EXE hypervolume)
add_executable(${EXE} ${SRC})

set_property(TARGET ${EXE} PROPERTY CXX_STANDARD 11)
