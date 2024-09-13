cmake_minimum_required(VERSION 3.22)

project(HELLOAPP VERSION 5.6)
set(PRODUCT_YEAR "2024")


set(SORSCE_FILES main.cpp src/calc.cpp )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)   #add lib/cmakelists

add_executable(hellobinary ${SORSCE_FILES})
target_include_directories(hellobinary PUBLIC include/ lib/)

configure_file(defaultconfig.h.in defaultconfig.h)
target_include_directories(hellobinary PUBLIC ${PROJECT_BINARY_DIR})



