cmake_minimum_required(VERSION 3.5)
list(APPEND CMAKE_PREFIX_PATH "F:\\Qt\\6.7.0\\mingw_64\\lib\\cmake")
list(APPEND CMAKE_PREFIX_PATH "F:\\Qt\\6.7.0\\mingw_64\\lib\\cmake\\Qt6")

set(Qt6GuiTools_DIR "F:\\Qt\\6.7.0\\mingw_64\\lib\\cmake\\Qt6GuiTools")
project(XOXO VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        board.h board.cpp
        historydialog.h historydialog.cpp historydialog.ui
        DatabaseManager.cpp  # Add this line if the addUser function is defined in this file
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(XOXO
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(XOXO SHARED
                ${PROJECT_SOURCES}
        )
    else()
        add_executable(XOXO
                ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(XOXO PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# rest of your CMakeLists.txt...