cmake_minimum_required(VERSION 3.21)
project(project VERSION 0.1.0)

set(BIN_DIR "${CMAKE_SOURCE_DIR}/build/${BUILD_TYPE_DIR}/${PLATFORM_DIR}")

add_subdirectory(flugel)
add_subdirectory(app)