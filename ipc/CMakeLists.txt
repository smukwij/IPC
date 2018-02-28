
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.cc
    )

set(HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.hh
    )


add_library(src STATIC ${SOURCES} ${HEADERS})

