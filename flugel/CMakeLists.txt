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

set(GLFW_FILES
  src/api/glfw/input/glfw_input.cpp
  src/api/glfw/input/glfw_keymap.cpp
  src/api/glfw/input/glfw_mousemap.cpp
  src/api/glfw/window/glfw_window.cpp
)

set(SDL2_FILES
  src/api/sdl2/input/sdl2_input.cpp
  src/api/sdl2/input/sdl2_keymap.cpp
  src/api/sdl2/input/sdl2_mousemap.cpp
  src/api/sdl2/window/sdl2_window.cpp
)

set(SHADER_FILES
  res/shaders/simple_shader.glsl)

# ===================================================
# ADD LIBRARY TARGET
# ===================================================
add_library(${TARGET_NAME}
  STATIC
    ${SOURCE_FILES}
)

if(FLUGEL_USE_GLFW)
  message(STATUS "Using GLFW!")
  target_sources(${TARGET_NAME} PRIVATE ${GLFW_FILES})
  target_compile_definitions(${TARGET_NAME} PUBLIC FLUGEL_USE_GLFW=1 GLFW_INCLUDE_NONE=1)
elseif(FLUGEL_USE_SDL2)
  message(STATUS "Using SDL2!")
  target_sources(${TARGET_NAME} PRIVATE ${SDL2_FILES})
  target_compile_definitions(${TARGET_NAME} PUBLIC FLUGEL_USE_SDL2=1)
endif()

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
  PUBLIC
    $<$<CONFIG:debug>:FLUGEL_ENABLE_ASSERTS=1>
    $<$<CONFIG:relwithdebinfo>:FLUGEL_ENABLE_ASSERTS=1>
)

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Export the library's public header path to dependent targets
# Define the include DIRs
target_include_directories(${TARGET_NAME}
  PRIVATE
    "src" "include"
  PUBLIC
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

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# PACKAGE
# boost
find_package(Boost REQUIRED
  COMPONENTS
    container
    coroutine
    log
    system
    thread
)
target_link_libraries(${TARGET_NAME}
  PUBLIC
    Boost::headers
    Boost::container
    Boost::coroutine
    Boost::log
    Boost::system
    Boost::thread
)

# glad
find_package(glad REQUIRED)
target_link_libraries(${TARGET_NAME}
  PRIVATE
    glad::glad
)

# HEADER ONLY
# stb
find_path(STB_INCLUDE_DIRS "stb.h" REQUIRED)
target_include_directories(${TARGET_NAME}
  PRIVATE
    ${STB_INCLUDE_DIRS}
)

# imgui
target_include_directories(${TARGET_NAME}
  PRIVATE
    "vendor/imgui"
)

# LIBRARY
if(FLUGEL_USE_GLFW)
  add_subdirectory(vendor/glfw)
  target_include_directories(${TARGET_NAME}
    PRIVATE
      "vendor/glfw/include"
  )
  target_link_libraries(${TARGET_NAME}
    PRIVATE
      glfw
  )
elseif(FLUGEL_USE_SDL2)
  add_subdirectory(vendor/sdl)
  target_include_directories(${TARGET_NAME}
    PRIVATE
      "vendor/sdl/include"
  )
  target_link_libraries(${TARGET_NAME}
    PRIVATE
      SDL2::SDL2
  )
endif()

# glm
add_subdirectory(vendor/glm)
target_include_directories(${TARGET_NAME}
  PRIVATE
    "vendor/glm"
)
target_link_libraries(${TARGET_NAME}
  PRIVATE
    glm::glm
)

# spdlog
add_subdirectory(vendor/spdlog)
target_include_directories(${TARGET_NAME}
  PRIVATE
    "vendor/spdlog/include"
)
target_link_libraries(${TARGET_NAME}
  PUBLIC
    spdlog::spdlog
)
