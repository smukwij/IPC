include_directories(${PROJECT_SOURCE_DIR}) 

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MyAsio.cc
    )

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/MyAsio.hh
   )


add_library(my_asio STATIC ${SOURCES} ${HEADERS})

add_executable(client ${CMAKE_CURRENT_SOURCE_DIR}/client/main.cc)
target_link_libraries(client ${INTERNAL_LIBS} ${EXTERNAL_LIBS})

add_executable(server ${CMAKE_CURRENT_SOURCE_DIR}/server/main.cc)
target_link_libraries(server ${INTERNAL_LIBS} ${EXTERNAL_LIBS})

