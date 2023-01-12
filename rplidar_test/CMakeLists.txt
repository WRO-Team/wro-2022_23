cmake_minimum_required(VERSION 3.0.0)
project(rplidar_test VERSION 0.1.0)

include_directories(include)

add_executable(rplidar_test src/main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries( ${PROJECT_NAME} PRIVATE Threads::Threads)

set(RPLIDAR_SDK_PATH "/home/pepe/Documents/wro-2022_23/lib/rplidar_sdk/")

add_library(rplidar STATIC IMPORTED)

set_property(TARGET rplidar
  PROPERTY IMPORTED_LOCATION ${RPLIDAR_SDK_PATH}output/Linux/Release/libsl_lidar_sdk.a)

target_include_directories(rplidar INTERFACE
  ${RPLIDAR_SDK_PATH}sdk/include/
  ${RPLIDAR_SDK_PATH}sdk/src/)
include_directories(include)

target_link_libraries(${PROJECT_NAME} PUBLIC rplidar)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
