
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging.cc
    )

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Logging.hh
    )


add_library(logging STATIC ${SOURCES} ${HEADERS})

