
cmake_minimum_required(VERSION 3.13)
project(cgi_reviews)
set(CMAKE_CXX_STANDARD 14)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
    set(EXECUTABLE_OUTPUT_PATH "C:/OpenServer/domains/localhost")
    add_executable(cgi_reviews main.cpp cgi/cgi.cpp cgi/cgi.h)
    set_target_properties(
            cgi_reviews
            PROPERTIES
            OUTPUT_NAME "reviews"
            SUFFIX ".cgi"
    )
else()
    add_executable(cgi_reviews main.cpp cgi/cgi.cpp cgi/cgi.h)
endif()