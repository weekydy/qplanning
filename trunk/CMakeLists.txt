project(QPlanning)

#set(EXECUTABLE_OUTPUT_PATH bin${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.4.0)
find_package(Qt4 4.6 REQUIRED)

add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(ts)
