cmake_minimum_required(VERSION 3.5)

project(GNSS_Commander LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GNSS_Commander main.cpp
                              src/pmtk.h
                              src/E108_Commander.h)

install(TARGETS GNSS_Commander
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
