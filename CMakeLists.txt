cmake_minimum_required(VERSION 3.20)

set(PROJECT 2dCAD)

project(${PROJECT} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(AUTOUIC ON)
set(AUTOMOC ON)
set(AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN "${PROJECT}_exec")

# path to qt6
set (QT_CONFIG_PATH /home/vk/Qt/6.3.1/gcc_64/lib/cmake)
list(APPEND CMAKE_PREFIX_PATH ${QT_CONFIG_PATH})

find_package(Qt6 REQUIRED COMPONENTS Widgets
									 Gui)

include(CTest)

add_subdirectory(src)
add_subdirectory(thirdParty/googletest)
add_subdirectory(tests)
