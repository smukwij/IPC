include_directories(${PROJECT_SOURCE_DIR}) 

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/process/Process.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/server/Server.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/client/Client.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/connection/Socket.cc
    )

set(HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/IpcMaster.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/process/Process.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/server/Server.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/client/Client.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/connection/Connection.hh
    ${CMAKE_CURRENT_SOURCE_DIR}/connection/Socket.hh
    )


add_library(ipc STATIC ${SOURCES} ${HEADERS})

