cmake_minimum_required(VERSION 3.16)
project(omnigrid_core_dsp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core_dsp
    src/engine.cpp
    src/queues.cpp
)

target_include_directories(core_dsp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
