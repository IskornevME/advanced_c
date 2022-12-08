cmake_minimum_required(VERSION 3.0.0)

project(set)
# set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

set(SET_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include/)
# file(GLOB HEADERS ${SET_INCLUDE_DIRS}/*.h)

# set(MATRIX_LIBRARIES ${PROJECT_NAME})

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${SET_INCLUDE_DIRS})

add_subdirectory(tests)
