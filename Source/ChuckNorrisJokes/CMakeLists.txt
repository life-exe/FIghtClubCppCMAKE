set(PROJECT_NAME ChuckNorrisJokes)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} raylib nlohmann_json::nlohmann_json #[===[cpr::cpr]===])
