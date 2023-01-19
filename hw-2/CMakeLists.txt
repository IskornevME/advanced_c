cmake_minimum_required(VERSION 3.0.0)
project(matrix)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/lib/*.cpp)

set(MATRIX_LIBRARIES ${PROJECT_NAME})
set(MATRIX_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/lib/)

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_INCLUDE_DIRS})

add_subdirectory(tests)
