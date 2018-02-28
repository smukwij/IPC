
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/process/Process.cc
    
    )

set(HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/process/Process.hh
    )


add_library(ipc STATIC ${SOURCES} ${HEADERS})

