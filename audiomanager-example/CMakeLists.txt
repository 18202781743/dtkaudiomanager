# SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
#
# SPDX-License-Identifier: LGPL-3.0-or-later

PROJECT(audiomanager-example)

include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB_RECURSE SRCS "main.cpp"
)

set(EXECUTABLE_OUTPUT_PATH ../)
set(REQUIRED_QT_VERSION 5.11.3)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(PulseAudio)
find_package(audiomanager)

add_executable(${PROJECT_NAME}
    ${SRCS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    ${PULSEAUDIO_LIBRARY}
    ${audiomanager_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    ${PULSEAUDIO_INCLUDE_DIR}
    ${audiomanager_INCLUDE_DIR}
)
