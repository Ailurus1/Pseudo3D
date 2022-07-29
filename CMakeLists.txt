cmake_minimum_required(VERSION 3.18)
project(Pseudo3D)
set(CMAKE_CXX_STANDARD 17)

set(HEADER_FILES Map.hpp Utils.hpp Player.hpp Constants.hpp Engine.hpp)
set(SOURCE_FILES Map.cpp Utils.cpp Player.cpp Engine.cpp)
set(EXECUTABLE main.cpp)

add_executable(${PROJECT_NAME} ${EXECUTABLE} ${SOURCE_FILES} ${HEADER_FILES})

set(SFML_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SFML/include/")
set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML/lib/cmake/SFML")
set(SFML_ROOT ${SFML_DIR})
set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-network sfml-graphics sfml-window sfml-system)