cmake_minimum_required(VERSION 3.22)
project(HELLOAPP)


set(SORSCE_FILES main.cpp src/calc.cpp)
# SET(SORSE_FILES "main.cpp;src/calc.cpp")

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)  


add_executable(hellobinary ${SORSCE_FILES})
target_include_directories(hellobinary PUBLIC include/ lib/)

target_link_libraries(hellobinary PUBLIC wifi_lib)


# message("from perant CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
# message("from perant CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}")

# message("from perant CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
# message("from perant CMAKE_CURRENT_BINARY_DIR:${CMAKE_CURRENT_BINARY_DIR}")

# message("from perant CMAKE_GENERATOR:${CMAKE_GENERATOR}")




