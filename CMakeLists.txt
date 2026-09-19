cmake_minimum_required(VERSION 3.20)
project(inverted_pendulum_rl LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

file(GLOB SOURCES CONFIGURE_DEPENDS src/*.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_executable(inverted_pendulum_rl ${SOURCES})
target_include_directories(inverted_pendulum_rl PRIVATE include)
target_link_libraries(inverted_pendulum_rl PRIVATE SFML::Graphics SFML::Window SFML::System)