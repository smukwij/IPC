
set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/process/Process.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/server/Server.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/client/Client.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/logging/Logging.cc
    )

set(HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/process/Process.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/server/Server.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/client/Client.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/logging/Logging.hh
    )


add_library(ipc STATIC ${SOURCES} ${HEADERS})

