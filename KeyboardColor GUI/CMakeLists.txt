cmake_minimum_required(VERSION 3.16)

project(KeyboardColor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    keyboardcoulour.cpp
    keyboardcoulour.h
    keyboardcoulour.ui
    appicon.rc
)


qt_add_executable(KeyboardColor
    ${PROJECT_SOURCES}
    resources.qrc
)


target_link_libraries(KeyboardColor PRIVATE Qt6::Widgets)


set(ICON_FILE_NAME "favicon.ico") 
set_target_properties(KeyboardColor PROPERTIES
    WIN32_EXECUTABLE ON
    WIN32_ICON "${ICON_FILE_NAME}"
)

