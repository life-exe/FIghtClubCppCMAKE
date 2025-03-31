set(PROJECT_NAME DoodleJumpGame)

add_executable(${PROJECT_NAME} main.cpp)

set(SOURCE_FILES
    DoodleJump.cpp
    DoodleJump.h
    Player.cpp
    Player.h
    Types.h
    PlatformManager.h
    PlatformManager.cpp
    pch.h
)
add_library(${PROJECT_NAME}Lib ${SOURCE_FILES})
target_precompile_headers(${PROJECT_NAME}Lib PRIVATE pch.h)
add_executable(${PROJECT_NAME}TestRunner Tests/main.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}Lib)
target_link_libraries(${PROJECT_NAME}Lib raylib MathLib)
target_link_libraries(${PROJECT_NAME}TestRunner ${PROJECT_NAME}Lib gtest::gtest)

target_include_directories(${PROJECT_NAME}TestRunner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}TestRunner PROPERTIES FOLDER ${PROJECT_NAME})

include(${CMAKE_SOURCE_DIR}/Automation/CMAKE/CMakeHelpers.cmake)
# setup_precompiled_headers(${PROJECT_NAME}Lib pch.cpp pch.h "${SOURCE_FILES}")
