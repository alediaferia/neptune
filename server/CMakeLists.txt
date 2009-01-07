project(Neptune-Server)

include(${QT_USE_FILE})

set (NeptuneServer_SRCS
main.cpp
serverdialog.cpp
neptuneserver.cpp
../client/connectioninfowidget.cpp
)

set (netuis_UIS
    server.ui
)

set (server_RCS
    resource.qrc
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ../client/
)

qt4_wrap_ui(NeptuneServer_SRCS ${netuis_UIS})
qt4_add_resources( NeptuneServer_SRCS ${server_RCS})
qt4_automoc(${NeptuneServer_SRCS})

add_executable(neptune-server ${NeptuneServer_SRCS})
target_link_libraries(neptune-server ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})

install( TARGETS neptune-server RUNTIME DESTINATION bin)