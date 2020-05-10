
cmake_minimum_required(VERSION 3.1)

project (Xotepad)

set (CMAKE_CXX_STANDARD 17)
set (WIN32PP_INCLUDE_PATH "" CACHE STRING "Win32++ Include Path")
set (SCINTILLA_INSTALL_PATH "" CACHE STRING "Scintilla Installation Path")

add_subdirectory ("./component/core")
include_directories ("./component/core/sources")

add_subdirectory ("./component/wtl-forms")
include_directories ("./component/wtl-forms/sources")

include_directories ("./dependencies/Catch2/single_include")
add_subdirectory ("./component/test-core")

include_directories ("./dependencies/wtl-git/Include")
add_subdirectory ("./component/Xotepad")
