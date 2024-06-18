cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
project(pacman LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(pacman src/main.cpp 
		              src/field.hpp
                      src/field.cpp
                      src/game_state.cpp
                      src/game_state.hpp
                      src/creatures.cpp
                      src/creatures.hpp
                      src/paths.hpp)
                      
find_package(SFML 2.5 COMPONENTS REQUIRED graphics)
target_link_libraries(pacman PRIVATE sfml-graphics)
target_compile_features(pacman PRIVATE cxx_std_20)

