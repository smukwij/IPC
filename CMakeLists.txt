cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_COMPILER /usr/bin/clang-5.0)
set(CMAKE_CXX_COMPILER /usr/bin/clang++-5.0)

project(ipcp)

set(CMAKE_CXX_FLAGS "-Werror -pedantic" )
set(CMAKE_EXE_LINKER_FLAG "")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/lib/boost/lib/boost_1_67_0/include)
find_package(Boost REQUIRED COMPONENTS system thread)

#link_directories(${CMAKE_SOURCE_DIR}/lib)
#link_directories(/usr/lib/x86_64-linux-gnu )
#link_directories(/usr/lib/x86_64-linux-gnu/)

include_directories(${CMAKE_SOURCE_DIR}/lib/boost/lib/boost_1_67_0/include)
include_directories(${Boost_INCLUDE_DIRS}) 


set(SOURCES
    ${CMAKE_SOURCE_DIR}/main.cc
    )

add_executable(ipcp ${SOURCES})

set(EXTERNAL_LIBS 
    pthread
    ${Boost_LIBRARIES}
)

set(INTERNAL_LIBS
    ipc
    my_asio
    logging
    )

add_subdirectory(ipc)
add_subdirectory(my_asio)
add_subdirectory(logging)


target_link_libraries(ipcp ${INTERNAL_LIBS} ${EXTERNAL_LIBS})



