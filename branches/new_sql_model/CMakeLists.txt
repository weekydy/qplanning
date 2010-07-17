project(QPlanning)

#set(EXECUTABLE_OUTPUT_PATH bin${CMAKE_BUILD_TYPE})
set(CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.4.2)
find_package(Qt4 4.6 REQUIRED)

set(PREFIX "/" CACHE PATH "prefix to install file : (usefull to packagers)")
set(PROGRAM_DIR_PREFIX "/usr/share/qplanning/" CACHE PATH "file path")
set(PROGRAM_DIR_EXECUTABLE "/usr/bin/" CACHE PATH "bin path")
set(TRANSLATION_DIR "/usr/share/qplanning/translations/" CACHE PATH "translations path")
set(DOC_DIR "/usr/share/doc/qplanning/" CACHE PATH "doc dir")
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(ts)

install(FILES ${CMAKE_SOURCE_DIR}/XmlSpec.xsd DESTINATION ${PREFIX}/${PROGRAM_DIR_PREFIX})
#install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/latex/ DESTINATION ${PREFIX}/${DOC_DIR})
#install(DIRECTORY ${CMAKE_BINARY_DIR}/doc/html/ DESTINATION ${PREFIX}/${DOC_DIR})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "free scool planning")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_EXECUTABLES "${CMAKE_BINARY_DIR}/bin/QPlanning")
include(CPack)
