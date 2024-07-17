# general info
cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME FightClubGame)
project(${PROJECT_NAME} VERSION 1.0.0)
message("------------- Project files generation for ${PROJECT_NAME} -------------")

# common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message("Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# cpp options
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /FA")

#app options
set(SOURCES 
    Source/main.cpp 
    Source/Utils/Math.cpp 
    Source/Game/Weapon.cpp 
    Source/Game/Character.cpp)

set(INCLUDES 
    Source/Utils/Math.h 
    Source/Game/Weapon.h 
    Source/Game/Character.h)

source_group("Source files/Utils" FILES "Source/Utils/Math.cpp")
source_group("Header files/Utils" FILES "Source/Utils/Math.h")

source_group("Source files/Game" FILES "Source/Game/Weapon.cpp" "Source/Game/Character.cpp")
source_group("Header files/Game" FILES "Source/Game/Weapon.h" "Source/Game/Character.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})

# includes
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

if(WIN32)
    message("Running on Windows")
elseif(LINUX)
    message("Running on Linux")
endif()

message("Using ${CMAKE_CXX_COMPILER_ID} compiler")
if(MSVC)
    message("MSVC version: ${MSVC_VERSION}")
    message("MSVC toolset version: ${MSVC_TOOLSET_VERSION}")
    target_compile_options(${PROJECT_NAME} PRIVATE /FAc)
endif()

message("Compiler flags: ${CMAKE_CXX_FLAGS}")
message("Compiler debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("Compiler release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message("Configuration types: ${CMAKE_CONFIGURATION_TYPES}")

