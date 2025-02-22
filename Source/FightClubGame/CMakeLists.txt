set(PROJECT_NAME FightClubGame)

set(SOURCES main.cpp)

set(DLL_GAME_SOURCES Game/Weapon.cpp Game/Character.cpp)
set(DLL_GAME_INCLUDES Game/Weapon.h Game/Character.h)

source_group("Source files/Game" FILES "Game/Weapon.cpp" "Game/Character.cpp")
source_group("Header files/Game" FILES "Game/Weapon.h" "Game/Character.h")

add_executable(${PROJECT_NAME} ${SOURCES})
add_library(${PROJECT_NAME}Lib SHARED ${DLL_GAME_SOURCES} ${DLL_GAME_INCLUDES})
add_executable(${PROJECT_NAME}TestRunner Tests/main.cpp)

target_compile_definitions(${PROJECT_NAME}Lib PRIVATE _EXPORTING)
target_compile_definitions(${PROJECT_NAME} PUBLIC _IMPORTING)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}Lib PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE MathLib)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE gtest::gtest)

set(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}TestRunner ${PROJECT_NAME}Lib)
foreach(target IN LISTS TARGETS)
    target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}TestRunner PROPERTIES FOLDER ${PROJECT_NAME})
