cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(dataset-tools)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -march=native")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -march=native")

FILE(GLOB GHEADERS "substract/*.h*")
FILE(GLOB GSOURCES "substract/*.cpp")

FILE(GLOB GUIHEADERS "gui/*.h*")
FILE(GLOB GUISOURCES "gui/*.cpp")

FILE(GLOB GUIPAGESHEADERS "gui/pages/*.h*")
FILE(GLOB GUIPAGESSOURCES "gui/pages/*.cpp")

#Find QT
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5SerialPort)

add_executable( main ${GUISOURCES} ${GUIHEADERS} ${GUIPAGESHEADERS} ${GUIPAGESSOURCES} )
target_link_libraries( main Qt5::Widgets Qt5::Core Qt5::SerialPort)

