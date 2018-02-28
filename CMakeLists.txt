cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_COMPILER /usr/bin/clang-5.0)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-5.0)

project(ipc)

set(CMAKE_CXX_FLAGS "-Werror -pedantic" )
set(CMAKE_EXE_LINKER_FLAG "")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#link_directories(${CMAKE_SOURCE_DIR}/lib)
#link_directories(/usr/lib/x86_64-linux-gnu )
#link_directories(/usr/lib/nvidia-384)

#include_directories(${CMAKE_SOURCE_DIR}/include)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/main.cc
    )

add_subdirectory(src)
#add_subdirectory(trainings)
#add_subdirectory(stb_image)

add_executable(ipc ${SOURCES})

target_link_libraries(ipc src)
