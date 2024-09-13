cmake_minimum_required(VERSION 3.22)

message(STATUS "hello from lib")

#link to files in wifi_lib.a
add_library(wifi_lib    
               wifi.cpp
               wifi.hpp)


# message("from lib CMAKE_SOURCE_DIR:${CMAKE_SOURCE_DIR}")
# message("from lib CMAKE_CURRENT_SOURCE_DIR:${CMAKE_CURRENT_SOURCE_DIR}")               
# message("from lib CMAKE_BINARY_DIR:${CMAKE_BINARY_DIR}")
# message("from lib CMAKE_CURRENT_BINARY_DIR:${CMAKE_CURRENT_BINARY_DIR}")               
# message("from lib CMAKE_GENERATOR:${CMAKE_GENERATOR}")

# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED true)
# message("CMAKE_CXX_STANDARD : ${CMAKE_CXX_STANDARD}")
# message("CMAKE_CXX_STANDARD_REQUIRED: ${CMAKE_CXX_STANDARD_REQUIRED}")

# MESSAGE(STATUS "ENG:-ATEF REDA")

# message("PATH: $ENV{PATH}")

# message("my name:${name}")

# message("CMAKE_CXX_STANDARD IS: ${CMAKE_CXX_STANDARD}")