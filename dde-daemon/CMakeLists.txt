# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

set(BIN_NAME dtkaudioddedaemon)

file(GLOB_RECURSE INCLUDE_PRIVATE_FILES
    "../include/daudioport_p.h"
    "../include/daudiocard_p.h"
    "../include/daudioplugin_p.h"
)
file(GLOB_RECURSE INCLUDE_FILES
    "./daudioport_daemon.h"
    "./daudiocard_daemon.h"
    "./daudioplugin_daemon.h"
    "./daudiomanager_daemon.h"
    "./daudiodevice_daemon.h"
)
file(GLOB_RECURSE SRCS
    "./daudioport_daemon.cpp"
    "./daudiocard_daemon.cpp"
    "./daudioplugin_daemon.cpp"
    "./daudiomanager_daemon.cpp"
    "./daudiodevice_daemon.cpp"
)

add_library(${BIN_NAME} SHARED
    ${INCLUDE_FILES}
    ${INCLUDE_PRIVATE_FILES}
    ${SRCS}
)

include_directories(../include)
include_directories(../src)

set_target_properties(${BIN_NAME} PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

target_compile_definitions(${BIN_NAME} PRIVATE VERSION="${CMAKE_PROJECT_VERSION}")

target_include_directories(${BIN_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    ${RSVG2_INCLUDE_DIRS}
)

target_link_libraries(${BIN_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::DBus
    ${RSVG2_LIBRARIES}
)

install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${BIN_NAME})
install(TARGETS ${BIN_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
