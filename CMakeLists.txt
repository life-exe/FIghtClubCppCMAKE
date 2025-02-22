# general info
cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME CMakeLearning)
project(${PROJECT_NAME} VERSION 1.0.0)

set(STARTUP_PROJECT_NAME FightClubGame)

# common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${STARTUP_PROJECT_NAME})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# cpp options
set(CMAKE_CXX_STANDARD 20)

# find libs
find_package(nlohmann_json REQUIRED)
find_package(GTest REQUIRED)
find_package(cpr)
find_package(raylib)

include_directories(Source)

add_subdirectory(Source/RaylibTetris)
add_subdirectory(Source/ChuckNorrisJokes)
add_subdirectory(Source/Utils)
add_subdirectory(Source/FightClubGame)

include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
system_info()
