cmake_minimum_required(VERSION 3.6)
project(RayTracing)

set(OPT_FLAGS "-Ofast -march=native -ffast-math -fno-rtti")

set(CMAKE_CXX_STANDARD 23)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror -Wno-unused-parameter -Wno-missing-field-initializers)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT_FLAGS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/linalg/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/image_tools/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/objects/*.hpp"
)

add_executable(RayTracing ${SOURCES} ./main.cpp)