cmake_minimum_required(VERSION 2.6)

CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

######################### The Project ##################################
project (Neptune)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set (Neptune_SRCS
main.cpp
mainwindow.cpp
serverdialog.cpp
connectioninfowidget.cpp
)

set (netuis_UIS
    neptune.ui
    server.ui
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR})

qt4_wrap_ui(Neptune_SRCS ${netuis_UIS})
qt4_automoc(${Neptune_SRCS})

add_executable(neptune ${Neptune_SRCS})
target_link_libraries(neptune ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTNETWORK_LIBRARY})

install( TARGETS neptune RUNTIME DESTINATION bin)
