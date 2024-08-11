# general info
# set(CMAKE_MESSAGE_LOG_LEVEL NOTICE)
cmake_minimum_required(VERSION 3.30)
set(PROJECT_NAME FightClubGame)
project(${PROJECT_NAME} VERSION 1.0.0)
message("------------- Project files generation for ${PROJECT_NAME} -------------")

# common options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
message("Output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_SUPPRESS_REGENERATION TRUE)

# cpp options
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /FA")

# sources
set(SOURCES Source/main.cpp)

set(MATH_SOURCES 
    Source/Utils/Math.cpp)

set(MATH_INCLUDES 
    Source/Utils/Math.h)

set(DLL_GAME_SOURCES
    Source/Game/Weapon.cpp 
    Source/Game/Character.cpp)

set(DLL_GAME_HEADERS
    Source/Game/Weapon.h 
    Source/Game/Character.h)

source_group("Source files/Game" FILES "Source/Game/Weapon.cpp" "Source/Game/Character.cpp")
source_group("Header files/Game" FILES "Source/Game/Weapon.h" "Source/Game/Character.h")

# targets
add_executable(${PROJECT_NAME} ${SOURCES} ${INCLUDES})
add_library(MathLib STATIC ${MATH_SOURCES} ${MATH_INCLUDES})
add_library(GameLib SHARED ${DLL_GAME_SOURCES} ${DLL_GAME_HEADERS})
add_executable(${PROJECT_NAME}TestRunner Source/Tests/main.cpp)

target_compile_definitions(GameLib PRIVATE _EXPORTING)
target_compile_definitions(${PROJECT_NAME} PRIVATE _IMPORTING)
option(SKIP_GAME_OPT "Skip game" ON)
if(SKIP_GAME_OPT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SKIP_GAME)
endif()

# target_link_libraries(${PROJECT_NAME} PRIVATE MathLib)
target_link_libraries(GameLib PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME} PRIVATE GameLib)

target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE GameLib)

# includes
set(TARGETS ${PROJECT_NAME} GameLib ${PROJECT_NAME}TestRunner)
foreach(target IN LISTS TARGETS)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
endforeach()

# target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
# target_include_directories(GameLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)
# target_include_directories(${PROJECT_NAME}TestRunner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)

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
    target_compile_options(MathLib PRIVATE /Zi)
endif()

message("Compiler flags: ${CMAKE_CXX_FLAGS}")
message("Compiler debug flags: ${CMAKE_CXX_FLAGS_DEBUG}")
message("Compiler release flags: ${CMAKE_CXX_FLAGS_RELEASE}")
message("Configuration types: ${CMAKE_CONFIGURATION_TYPES}")

# cmake --build . --clean-first -v --config Release --target MathLib
# --log-level=ERROR

# options + UI
# github workflow

