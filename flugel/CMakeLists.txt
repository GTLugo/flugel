# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.16)
project(flugel VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME "flugel")
message(STATUS "Configuring: ${PROJECT_NAME}")

# BIN_DIR uses highest level cmake source dir
#set(BIN_DIR  "${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}")
# set(SRC_DIR  "src")
# set(LIB_DIR  "lib")
# set(INCL_DIR "include")
# set(RES_DIR  "res")

# ===================================================
# COLLECT FILES
# ===================================================

# file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
#   ${SRC_DIR}/*.c
#   ${SRC_DIR}/*.cpp)
# file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
#   ${SRC_DIR}/*.h
#   ${SRC_DIR}/*.hpp)
# file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
#   RELATIVE ${CMAKE_SOURCE_DIR} 
#   ${RES_DIR}/*.glsl)

set(SOURCE_FILES
  src/core/app.cpp
  src/core/uuid.cpp
  src/core/logging/log.cpp
  src/core/time/time.cpp
  src/core/events/notifier.cpp
  src/core/window/window.cpp)

set(HEADER_FILES
  src/flugel.hpp
  src/core/utilities.hpp
  src/core/entry_point.hpp
  src/core/app.hpp
  src/core/uuid.hpp
  src/core/logging/log.hpp
  src/core/time/time.hpp
  src/core/events/notifier.hpp
  #src/core/events/event.hpp
  src/core/events/keyboard_event.hpp
  src/core/events/mouse_event.hpp
  src/core/events/window_event.hpp
  src/core/events/app_event.hpp
  src/core/window/window.hpp
  )

set(SHADER_FILES
  res/shaders/simple_shader.glsl)

# ===================================================
# CONFIGURE ASSESTS HELPER FILE
# ===================================================
configure_file(src/helpers/RootDir.hpp.in src/helpers/RootDir.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

# ===================================================
# ADD SHARED LIBRARY TARGET
# ===================================================
add_library(${TARGET_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(${TARGET_NAME}
  PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}"
    CXX_VISIBILITY_PRESET hidden
    #RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
)
message(DEBUG "Engine bin Dir: ${BIN_DIR}")

# Preprocessor Defines
target_compile_definitions(${TARGET_NAME} PRIVATE 
  $<$<CONFIG:debug>:DEBUG=1 FLUGEL_ENABLE_ASSERTS=1>
  $<$<CONFIG:release>:RELEASE=1>
  $<$<CONFIG:relwithdebinfo>:RELDEB=1 FLUGEL_ENABLE_ASSERTS=1>
  $<$<CONFIG:minsizerel>:MINREL=1>
  FLUGEL_BUILD_DLL=1)

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

## glew
#message(CHECK_START "Finding glew...")
#find_package(glew CONFIG REQUIRED)
#set(GLEW_LIBRARY GLEW::GLEW)
#message(CHECK_PASS "found!")
#
## glad
#message(CHECK_START "Finding glad...")
#find_package(glad CONFIG REQUIRED)
#set(GLAD_LIBRARY glad::glad)
#message(CHECK_PASS "found!")
#
## glfw3
#message(CHECK_START "Finding glfw3...")
#find_package(glfw3 CONFIG REQUIRED)
#set(GLFW_LIBRARY glfw)
#message(CHECK_PASS "found!")

message(CHECK_START "Finding sdl2...")
find_package(SDL2 CONFIG REQUIRED)
set(SDL2_LIBRARY SDL2::SDL2) # SDL2::SDL2main
message(CHECK_PASS "found!")

# glm
message(CHECK_START "Finding glm...")
find_package(glm CONFIG REQUIRED)
set(GLM_LIBRARY glm::glm)
message(CHECK_PASS "found!")

# fmt
message(CHECK_START "Finding fmt...")
find_package(fmt CONFIG REQUIRED)
set(FMT_LIBRARY fmt::fmt-header-only)
message(CHECK_PASS "found!")

# spdlog
message(CHECK_START "Finding spdlog...")
find_package(spdlog CONFIG REQUIRED)
set(SPDLOG_LIBRARY spdlog::spdlog_header_only) #spdlog::spdlog OR spdlog::spdlog_header_only
message(CHECK_PASS "found!")

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Export the library's public header path to dependent targets
set(PUBLIC_HEADER_FILES "src")
# Define the include DIRs
target_include_directories(${TARGET_NAME}
  PUBLIC
    "src" "include"
  INTERFACE
    "${PUBLIC_HEADER_FILES}"
)


# Precompiled Headers
target_precompile_headers(${TARGET_NAME}
  PUBLIC
    "src/flugel_pch.hpp"
)

# Define the link libraries
link_directories("lib")

# Put all libraries into a variable & link the libraries
set(LIBS
#  ${GLEW_LIBRARY}
#  ${GLAD_LIBRARY}
#  ${GLFW_LIBRARY}
  ${SDL2_LIBRARY}
  ${GLM_LIBRARY}
  ${FMT_LIBRARY}
  ${SPDLOG_LIBRARY})

target_link_libraries(${TARGET_NAME} ${LIBS})