cmake_minimum_required(VERSION 3.22)

project(HELLOAPP VERSION 5.6)
set(PRODUCT_YEAR "2024")


set(SORSCE_FILES main.cpp src/calc.cpp )

add_subdirectory(${CMAKE_SOURCE_DIR}/lib)   #add lib/cmakelists

add_executable(hellobinary ${SORSCE_FILES})
target_include_directories(hellobinary PUBLIC include/ lib/)



configure_file(defaultconfig.h.in defaultconfig.h)
target_include_directories(hellobinary PUBLIC ${PROJECT_BINARY_DIR})


# foreach(F IN ITEMS A T E F R E D A)
#     MESSAGE(STATUS "${F}")
# endforeach()
# SET(LST A T E F R E D A)

# foreach(F IN LISTS LST)
#     MESSAGE(STATUS "${F}")
# endforeach()

set(var 10)
while(var)
    message("var:${var}")
    math(EXPR var "${var}-1")
endwhile(var)


