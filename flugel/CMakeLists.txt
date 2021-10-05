# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.16)
project(flugel VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME "flugel")
message(STATUS "Configuring: ${PROJECT_NAME}")

# ===================================================
# COLLECT FILES
# ===================================================

set(SOURCE_FILES
  src/core/app.cpp
  src/core/uuid.cpp
  src/core/logging/log.cpp
  src/core/time/time.cpp
  src/core/color/color.cpp
  src/core/color/srgb_transform/srgb_transform.cpp
  src/core/events/notifier.cpp
  src/core/window/window.cpp)

set(SHADER_FILES
  res/shaders/simple_shader.glsl)

# ===================================================
# ADD SHARED LIBRARY TARGET
# ===================================================
add_library(${TARGET_NAME}
  SHARED
    ${SOURCE_FILES}
)
set_target_properties(${TARGET_NAME}
  PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}"
    CXX_VISIBILITY_PRESET hidden
)
message(DEBUG "Engine bin Dir: ${BIN_DIR}")

# Preprocessor Defines
target_compile_definitions(${TARGET_NAME}
  PRIVATE 
    $<$<CONFIG:debug>:DEBUG=1 FLUGEL_ENABLE_ASSERTS=1>
    $<$<CONFIG:release>:RELEASE=1>
    $<$<CONFIG:relwithdebinfo>:RELDEB=1 FLUGEL_ENABLE_ASSERTS=1>
    $<$<CONFIG:minsizerel>:MINREL=1>
    FLUGEL_BUILD_DLL=1
)

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# glew
message(CHECK_START "Finding glew...")
find_package(glew CONFIG REQUIRED)
set(GLEW_LIBRARY PUBLIC GLEW::GLEW)
message(CHECK_PASS "found!")

# glad
message(CHECK_START "Finding glad...")
find_package(glad CONFIG REQUIRED)
set(GLAD_LIBRARY PUBLIC glad::glad)
message(CHECK_PASS "found!")

# glfw3
message(CHECK_START "Finding glfw3...")
find_package(glfw3 CONFIG REQUIRED)
set(GLFW_LIBRARY PUBLIC glfw)
message(CHECK_PASS "found!")

# glm
message(CHECK_START "Finding glm...")
find_package(glm CONFIG REQUIRED)
set(GLM_LIBRARY PUBLIC glm::glm)
message(CHECK_PASS "found!")

# fmt
message(CHECK_START "Finding fmt...")
find_package(fmt CONFIG REQUIRED)
set(FMT_LIBRARY PUBLIC fmt::fmt-header-only)
message(CHECK_PASS "found!")

# spdlog
message(CHECK_START "Finding spdlog...")
find_package(spdlog CONFIG REQUIRED)
set(SPDLOG_LIBRARY PUBLIC spdlog::spdlog_header_only) #spdlog::spdlog OR spdlog::spdlog_header_only
message(CHECK_PASS "found!")

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Export the library's public header path to dependent targets
# Define the include DIRs
target_include_directories(${TARGET_NAME}
  PRIVATE
    "src" "include"
  INTERFACE
    "src"
)


# Precompiled Headers
target_precompile_headers(${TARGET_NAME}
  PUBLIC
    "src/flugel_pch.hpp"
)

# Define the link libraries
target_link_directories(${TARGET_NAME}
  PRIVATE
    "lib"
)

# Put all libraries into a variable & link the libraries
set(LIBS
  ${GLEW_LIBRARY}
  ${GLAD_LIBRARY}
  ${GLFW_LIBRARY}
  ${GLM_LIBRARY}
  ${FMT_LIBRARY}
  ${SPDLOG_LIBRARY}
)

target_link_libraries(${TARGET_NAME}
  ${LIBS}
)