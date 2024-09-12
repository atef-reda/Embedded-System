cmake_minimum_required(VERSION 3.22)

message(STATUS "hello from lib")

#link to files in wifi_lib.a
add_library(wifi_lib    
               wifi.cpp
               wifi.hpp)