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
  src/api/glfw/input/glfw_input.cpp
  src/api/glfw/input/glfw_keymap.cpp
  src/api/glfw/input/glfw_mousemap.cpp
  src/api/glfw/window/glfw_window.cpp
  src/core/callbacks/notifier/notifier.cpp
  src/core/imgui/imgui_layer.cpp
  src/core/input/mouse_codes.cpp
  src/core/input/key_codes.cpp
  src/core/layers/engine_layer.cpp
  src/core/layers/layer_stack.cpp
  src/core/layers/layer.cpp
  src/core/thread_pool/thread_pool.cpp
  src/core/window/window.cpp
  src/core/app.cpp
  src/util/color/srgb_transform/srgb_transform.cpp
  src/util/color/color.cpp
  src/util/logging/log.cpp
  src/util/time/time.cpp
  src/util/uuid.cpp)

set(SHADER_FILES
  res/shaders/simple_shader.glsl)
# file(GLOB_RECURSE RES_FILES CONFIGURE_DEPENDS
#   RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/res
#   res/*.*)

# foreach(RES_FILE ${RES_FILES})
#   configure_file(res/${RES_FILE} ${WORKING_DIRECTORY}/res/${RES_FILE} COPYONLY)
# endforeach()

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

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E remove_directory
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/${PROJECT_NAME}")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/res/${PROJECT_NAME}
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/${PROJECT_NAME}")

# Preprocessor Defines
target_compile_definitions(${TARGET_NAME}
  PRIVATE
    $<$<CONFIG:debug>:DEBUG=1>
    $<$<CONFIG:release>:RELEASE=1>
    $<$<CONFIG:relwithdebinfo>:RELDEB=1>
    $<$<CONFIG:minsizerel>:MINREL=1>
    FLUGEL_BUILD_DLL=1
    GLFW_INCLUDE_NONE=1
  PUBLIC
    FLUGEL_USE_GLFW=1
    $<$<CONFIG:debug>:FLUGEL_ENABLE_ASSERTS=1>
    $<$<CONFIG:relwithdebinfo>:FLUGEL_ENABLE_ASSERTS=1>
)

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# boost
message(CHECK_START "Finding boost...")
find_package(Boost REQUIRED
  COMPONENTS
    container
    coroutine
    log
    system
    thread
)
set(BOOST_LIBRARIES
  PUBLIC
    Boost::headers
    Boost::container
    Boost::coroutine
    Boost::log
    Boost::system
    Boost::thread
)
message(CHECK_PASS "found!")

# stb
message(CHECK_START "Finding glad...")
find_path(STB_INCLUDE_DIRS "stb.h" REQUIRED)
message(CHECK_PASS "found!")

# fmt
message(CHECK_START "Finding fmt...")
find_package(fmt REQUIRED)
set(FMT_LIBRARY PUBLIC fmt::fmt-header-only)
message(CHECK_PASS "found!")

# spdlog
message(CHECK_START "Finding spdlog...")
find_package(spdlog REQUIRED)
set(SPDLOG_LIBRARY PUBLIC spdlog::spdlog_header_only) #spdlog::spdlog OR spdlog::spdlog_header_only
message(CHECK_PASS "found!")

# imgui
message(CHECK_START "Finding imgui...")
find_package(imgui REQUIRED)
set(IMGUI_LIBRARY PUBLIC imgui::imgui)
message(CHECK_PASS "found!")

# glad
message(CHECK_START "Finding glad...")
find_package(glad REQUIRED)
set(GLAD_LIBRARY PUBLIC glad::glad)
message(CHECK_PASS "found!")

# glfw3
message(CHECK_START "Finding glfw3...")
find_package(glfw3 REQUIRED)
set(GLFW_LIBRARY PUBLIC glfw)
message(CHECK_PASS "found!")

# glm
message(CHECK_START "Finding glm...")
find_package(glm REQUIRED)
set(GLM_LIBRARY PUBLIC glm::glm)
message(CHECK_PASS "found!")


# ===================================================
# INCLUDING & LINKING
# ===================================================
# Export the library's public header path to dependent targets
# Define the include DIRs
target_include_directories(${TARGET_NAME}
  PRIVATE
    "src" "include"
    ${STB_INCLUDE_DIRS}
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
  ${BOOST_LIBRARIES}
  ${FMT_LIBRARY}
  ${SPDLOG_LIBRARY}
  ${IMGUI_LIBRARY}
  ${GLAD_LIBRARY}
  ${GLFW_LIBRARY}
  ${GLM_LIBRARY}
)

target_link_libraries(${TARGET_NAME}
  ${LIBS}
)