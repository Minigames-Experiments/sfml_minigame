cmake_minimum_required (VERSION 3.10.0)
project (sfml_example LANGUAGES CXX)

# lots of warnings and all warnings as errors
add_compile_options(-Wall -Wextra -pedantic ) #-Werror

# find sfml
find_package(SFML 2.5 REQUIRED system window graphics network audio)

### Build the library ###

## Setup c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## If you want to link SFML statically
set(SFML_STATIC_LIBRARIES TRUE)

## Get all sources
file(GLOB_RECURSE SRCS src/*.cpp)

## Specify include directories
include_directories(
  ${SFML_INCLUDE_PATH}
  /opt/SFML-2.5.1/include
  src
)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} sfml-graphics sfml-audio)