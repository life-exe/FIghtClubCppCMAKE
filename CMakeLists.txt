# general info
cmake_minimum_required(VERSION 3.30)

# setup conan profiles
set(PROFILE_PATH_Windows_Release "${CMAKE_CURRENT_SOURCE_DIR}/conanProfiles/windowsRelease")
set(PROFILE_PATH_Windows_Debug "${CMAKE_CURRENT_SOURCE_DIR}/conanProfiles/windowsDebug")
set(PROFILE_PATH_Linux_Release "${CMAKE_CURRENT_SOURCE_DIR}/conanProfiles/linuxRelease")
set(PROFILE_PATH_Linux_Debug "${CMAKE_CURRENT_SOURCE_DIR}/conanProfiles/linuxDebug")

set(CURRENT_PROFILE "PROFILE_PATH_${CMAKE_HOST_SYSTEM_NAME}_${CMAKE_BUILD_TYPE}")
message(STATUS "Set conan profile: ${CURRENT_PROFILE}")

if(DEFINED ${CURRENT_PROFILE})
    set(CONAN_PROFILE "${${CURRENT_PROFILE}}")
    message(STATUS "Using conan profile: ${CONAN_PROFILE}")
else()
    message(FATAL_ERROR "Unsupported configuration for: ${CURRENT_PROFILE}")
endif()

include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
setup_conan(${CONAN_PROFILE} ${CONAN_PROFILE})

# common options
set(PROJECT_NAME CMakeLearning)
project(${PROJECT_NAME} VERSION 1.0.0)

set(STARTUP_PROJECT_NAME FightClubGame)

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
# find_package(cpr)
find_package(raylib)

include_directories(Source)

add_subdirectory(Source/RaylibTetris)
add_subdirectory(Source/ChuckNorrisJokes)
add_subdirectory(Source/Utils)
add_subdirectory(Source/FightClubGame)
add_subdirectory(Source/DoodleJumpGame)

system_info()
