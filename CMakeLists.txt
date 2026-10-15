cmake_minimum_required(VERSION 3.20)
project(inverted_pendulum
    VERSION 1.0.0
    DESCRIPTION "Inverted Pendulum Reinforcement Learning"
    LANGUAGES CXX
)

# 1. Global Configurations
# Set default build type to Release if none is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Generate compile_commands.json for IDEs (LSP, clangd, VSCode)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Route output files to clean, dedicated directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# 2. Dependencies
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# 3. Core Library Target
# Separating the core logic from main.cpp allows you to easily add unit tests later
file(GLOB CORE_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
list(REMOVE_ITEM CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

add_library(rl_core STATIC ${CORE_SOURCES})

# Enforce C++17 at the target level
target_compile_features(rl_core PUBLIC cxx_std_17)

# Set include directories
target_include_directories(rl_core PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Add robust compiler warnings
if(MSVC)
    target_compile_options(rl_core PRIVATE /W4)
else()
    target_compile_options(rl_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link SFML to the core library
target_link_libraries(rl_core PUBLIC 
    SFML::Graphics 
    SFML::Window 
    SFML::System
)

# 4. Main Executable Target
add_executable(inverted_pendulum_rl src/main.cpp)

# Link the core library to the executable
target_link_libraries(inverted_pendulum_rl PRIVATE rl_core)