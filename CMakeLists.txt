cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(LL)
set(CMAKE_CXX_STANDARD 17)

find_library(D2D1_LIBRARY d2d1)

if(NOT D2D1_LIBRARY)
    message(FATAL_ERROR "Direct2D library not found.")
endif()

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(LL "${MY_SOURCES}")

target_include_directories(LL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(LL PUBLIC ${D2D1_LIBRARY})

#to build
#$ cmake -S ../ -B Build -G "MinGW Makefiles"