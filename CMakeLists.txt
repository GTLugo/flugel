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
    src/core/renderer/buffer/buffer.cpp
    src/core/renderer/vertex_array/vertex_array.cpp
    src/core/renderer/buffer/frame_buffer.cpp
    src/core/renderer/buffer/texture_buffer.cpp
    src/core/renderer/context.cpp
    src/core/renderer/renderer.cpp
    src/core/renderer/render_dispatcher.cpp
    src/core/renderer/shader.cpp
    src/core/entities/camera/camera.cpp
    src/core/threading/thread_pool.cpp
    src/core/threading/job_system.cpp
    src/core/window/window.cpp
    src/core/app.cpp
    src/util/color/srgb_transform/srgb_transform.cpp
    src/util/color/color.cpp
    src/util/logging/log.cpp
    )

set(OPENGL_FILES
    src/api/opengl/context/opengl_context.cpp
    src/api/opengl/framebuffer/opengl_buffer.cpp
    src/api/opengl/vertex_array/opengl_vertex_array.cpp
    src/api/opengl/opengl_render_dispatcher.cpp
    src/api/opengl/framebuffer/opengl_frame_buffer.cpp
    src/api/opengl/framebuffer/opengl_texture_buffer.cpp
    src/api/opengl/opengl_shader.cpp
    )

set(VULKAN_FILES

    )

set(D3D11_FILES

    )

set(GLFW_FILES
    src/api/glfw/input/glfw_input.cpp
    src/api/glfw/input/glfw_keymap.cpp
    src/api/glfw/input/glfw_mousemap.cpp
    src/api/glfw/window/glfw_window.cpp
    )

set(SHADER_FILES
    res/shaders/simple_shader.glsl)

# ===================================================
# ADD LIBRARY TARGET
# ===================================================
add_library(${TARGET_NAME} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET_NAME}
    PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}"
    CXX_VISIBILITY_PRESET hidden)

# Copy resources folder into output dir
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
    _CRT_SECURE_NO_WARNINGS=1
    PUBLIC
    $<$<CONFIG:debug>:FLUGEL_ENABLE_ASSERTS=1>
    $<$<CONFIG:relwithdebinfo>:FLUGEL_ENABLE_ASSERTS=1>
    )

target_compile_options(${TARGET_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /WX>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-W3 -Werror>
    )
#file(GLOB_RECURSE VENDOR_SRCS "vendor/*.c*" "vendor/*.h*")
#set_source_files_properties(${VENDOR_SRCS}
#    PROPERTIES
#    COMPILE_OPTIONS "$<$<CXX_COMPILER_ID:MSVC>:/w>;$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>"
#    )
#set(COMPILER_FLAGS "$<$<CXX_COMPILER_ID:MSVC>:/W4;/WX>;$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall;-Wextra;-Wpedantic;-Werror>")

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Export the library's public header path to dependent targets
# Define the include DIRs
target_include_directories(${TARGET_NAME}
    PUBLIC
    "src" "include"
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

# PACKAGES
# boost
#set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost REQUIRED
    COMPONENTS
    container
    coroutine
    log
    system
    thread
    random
    )
target_link_libraries(${TARGET_NAME}
    PUBLIC
    Boost::headers
    Boost::container
    Boost::coroutine
    Boost::log
    Boost::system
    Boost::thread
    Boost::random
    )

# SUBMODULES
# glm
add_subdirectory(vendor/glm)
target_include_directories(${TARGET_NAME}
    PUBLIC
    "vendor/glm"
    )
target_link_libraries(${TARGET_NAME}
    PUBLIC
    glm::glm
    )
#target_compile_options(glm INTERFACE
#    $<$<CXX_COMPILER_ID:MSVC>:/w>
#    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>
#    )

# spdlog
add_subdirectory(vendor/spdlog)
target_include_directories(${TARGET_NAME}
    PUBLIC
    "vendor/spdlog/include"
    )
target_link_libraries(${TARGET_NAME}
    PUBLIC
    spdlog::spdlog
    )
#target_compile_options(spdlog PRIVATE
#    $<$<CXX_COMPILER_ID:MSVC>:/w>
#    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>
#    )

# imgui
target_include_directories(${TARGET_NAME}
    PUBLIC
    "vendor/imgui"
    )
target_sources(${TARGET_NAME}
    PUBLIC
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/imgui.cpp
    )
# IMGUI RENDER
if("OPENGL" IN_LIST FLUGEL_RENDERING_API)
  target_sources(${TARGET_NAME} PRIVATE vendor/imgui/backends/imgui_impl_opengl3.cpp)
endif()
if("VULKAN" IN_LIST FLUGEL_RENDERING_API)
  target_sources(${TARGET_NAME} PRIVATE vendor/imgui/backends/imgui_impl_vulkan.cpp)
endif()
if("D3D11" IN_LIST FLUGEL_RENDERING_API)
  target_sources(${TARGET_NAME} PRIVATE vendor/imgui/backends/imgui_impl_dx11.cpp)
endif()
# IMGUI WINDOW
target_sources(${TARGET_NAME} PRIVATE vendor/imgui/backends/imgui_impl_glfw.cpp)

# ===================================================
# API SPECIFICS
# ===================================================
# RENDER API
if("OPENGL" IN_LIST FLUGEL_RENDERING_API)
  message(STATUS "Using OPENGL!")
  target_sources(${TARGET_NAME} PRIVATE ${OPENGL_FILES})
  target_compile_definitions(${TARGET_NAME} PUBLIC FLUGEL_USE_OPENGL=1)
  # glad
  set(GLAD_SOURCES_DIR ${PROJECT_SOURCE_DIR}/vendor/glad)
  add_subdirectory(${GLAD_SOURCES_DIR}/cmake glad_cmake)
  set(GLAD_LIBRARY glad_gl_core_mx_global_46)
  glad_add_library(${GLAD_LIBRARY}
      STATIC MX GLOBAL API # #MX
      gl:core=4.6
      )
  target_link_libraries(${TARGET_NAME}
      PRIVATE
      ${GLAD_LIBRARY}
      )
#  target_compile_options(${GLAD_LIBRARY} PRIVATE
#      $<$<CXX_COMPILER_ID:MSVC>:/w>
#      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>
#      )
endif()
if("VULKAN" IN_LIST FLUGEL_RENDERING_API)
  message(STATUS "Using VULKAN!")
  target_sources(${TARGET_NAME} PRIVATE ${VULKAN_FILES})
  target_compile_definitions(${TARGET_NAME} PUBLIC FLUGEL_USE_VULKAN=1)
  # glad
  set(GLAD_SOURCES_DIR ${PROJECT_SOURCE_DIR}/vendor/glad)
  add_subdirectory(${GLAD_SOURCES_DIR}/cmake glad_cmake)
  set(GLAD_LIBRARY glad_vulkan_12)
  glad_add_library(${GLAD_LIBRARY}
      STATIC API MX #GLOBAL
      vulkan=1.2
      )
  target_link_libraries(${TARGET_NAME}
      PRIVATE
      ${GLAD_LIBRARY}
      )
#  target_compile_options(${GLAD_LIBRARY} PRIVATE
#      $<$<CXX_COMPILER_ID:MSVC>:/w>
#      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>
#      )
  # vulkan
  find_package(Vulkan REQUIRED)
  target_include_directories(${TARGET_NAME}
      PRIVATE
      ${Vulkan_INCLUDE_DIRS}
      )
  target_link_libraries(${TARGET_NAME}
      PRIVATE
      ${Vulkan_LIBRARIES}
      )
endif()
if("D3D11" IN_LIST FLUGEL_RENDERING_API)
  message(STATUS "Using D3D11!")
  target_sources(${TARGET_NAME} PRIVATE ${D3D11_FILES})
  target_compile_definitions(${TARGET_NAME} PUBLIC FLUGEL_USE_D3D11=1)
#  target_compile_options(${GLAD_LIBRARY} PRIVATE
#      $<$<CXX_COMPILER_ID:MSVC>:/w>
#      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-w>
#      )
endif()

# WINDOW API
message(STATUS "Using GLFW!")
target_sources(${TARGET_NAME} PRIVATE ${GLFW_FILES})
target_compile_definitions(${TARGET_NAME} PUBLIC FLUGEL_USE_GLFW=1 GLFW_INCLUDE_NONE=1)
add_subdirectory(vendor/glfw)
target_include_directories(${TARGET_NAME}
    PRIVATE
    "vendor/glfw/include"
    )
target_link_libraries(${TARGET_NAME}
    PRIVATE
    glfw
    )