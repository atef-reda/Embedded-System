cmake_minimum_required(VERSION 3.22)
project(HELLOAPP)


set(SORSCE_FILES main.cpp src/calc.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)  


add_executable(hellobinary ${SORSCE_FILES})
target_include_directories(hellobinary PUBLIC include/ lib/)

target_link_libraries(hellobinary PUBLIC wifi_lib)

