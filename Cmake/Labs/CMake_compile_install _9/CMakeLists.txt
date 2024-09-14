cmake_minimum_required(VERSION 3.22)

project(HELLOAPP VERSION 5.6)
set(PRODUCT_YEAR "2024")


set(SORSCE_FILES main.cpp src/calc.cpp )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)   #add lib/cmakelists


# message("${ATEF_AGE}")

add_executable(hellobinary ${SORSCE_FILES})
target_include_directories(hellobinary PUBLIC include/ lib/)

target_compile_definitions(hellobinary PUBLIC "ATEF_AGE=20") 
target_compile_options(hellobinary PUBLIC -march=native)


configure_file(defaultconfig.h.in defaultconfig.h)
target_include_directories(hellobinary PUBLIC ${PROJECT_BINARY_DIR})

install(FILES "${PROJECT_BINARY_DIR}/hellobinary.exe"
        DESTINATION "${PROJECT_BINARY_DIR}/executable")

install(FILES
        "${CMAKE_SOURCE_DIR}/lib/wifi.hpp"
        "${CMAKE_SOURCE_DIR}/include/calc.hpp"
        DESTINATION "${PROJECT_BINARY_DIR}/include")
#function
# function(myfirstfun arg1)
#     message("ARG1: ${arg1}") #arg name 
#     message("ARG1: ${${arg1}}") #arg value
#     message("name extra: ${ARGN}") #name extra arg
#     message("ARG1: ${${ARGN}}") #value extra arg
#     message("ARG1: ${ARGC}") #count of args
# endfunction(myfirstfun arg1)
# set(var  1 2 3 4)
# set(jan 2 4 5)
# set(jan1 2 4 5)
#we can pass extra arg than on decleration 
# myfirstfun(var jan jan1)

#CMakeCache.txt
# after generate code makefile throw command  cmake -G "MinGW Makefiles" .. 
# it generate CMakeCache.txt which store your MinGW Makefiles" and build in variable
# which you overried on

# we can store not build in variable in cach from to methods
# 1-
# option(cachvar1 "comment on this var" TRUE)
# set(cachvar2 FALSE CACHE BOOL "comment on this var")













