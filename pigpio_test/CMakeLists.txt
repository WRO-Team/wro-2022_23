cmake_minimum_required(VERSION 3.0.0)
project(pigpio_test VERSION 0.1.0)

include(GNUInstallDirs)

find_package(PkgConfig)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules) 

find_package(pigpio REQUIRED)

include_directories( ${pigpio_INCLUDE_DIRS})

add_executable(pigpio_test main.cpp)

target_link_libraries( pigpio_test ${pigpio_LIBRARY})

