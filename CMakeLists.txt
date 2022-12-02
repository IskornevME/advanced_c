cmake_minimum_required(VERSION 3.0.0)
project(schedule)

add_subdirectory(database)
add_subdirectory(task)

# message("DB_LIB_INCLUDE_DIRS = ${DB_LIB_INCLUDE_DIRS}")
# message("DB_LIB_LIBRARIES = ${DB_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

target_include_directories(${PROJECT_NAME} PUBLIC ${DB_LIB_INCLUDE_DIRS} ${TASK_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${DB_LIB_LIBRARIES} ${TASK_LIB_LIBRARIES})

add_subdirectory(tests)