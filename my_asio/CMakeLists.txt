
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MyAsio.cc
    )

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/MyAsio.hh
   )


add_library(my_asio STATIC ${SOURCES} ${HEADERS})

