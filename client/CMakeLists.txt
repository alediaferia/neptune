include(${QT_USE_FILE})

set (Neptune_SRCS
main.cpp
mainwindow.cpp
connectioninfowidget.cpp
)

set (netuis_UIS
    neptune.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ../server/
)

qt4_wrap_ui(Neptune_SRCS ${netuis_UIS})
qt4_automoc(${Neptune_SRCS})

add_executable(neptune ${Neptune_SRCS})
target_link_libraries(neptune ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})

install( TARGETS neptune RUNTIME DESTINATION bin)
