# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.21)
project(flugel_engine VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME "libflugel")
message(STATUS "Configuring: ${PROJECT_NAME}")

# BIN_DIR uses highest level cmake source dir
set(BIN_DIR  "${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_NAME}")
set(SRC_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(INCL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(RES_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/res")

# ===================================================
# COLLECT FILES
# ===================================================
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
     ${SRC_DIR}/*.c
     ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
     ${SRC_DIR}/*.h
     ${SRC_DIR}/*.hpp)
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS
     RELATIVE ${CMAKE_SOURCE_DIR} 
     ${RES_DIR}/*.glsl)

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
	     RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
message(DEBUG "Engine bin Dir: ${BIN_DIR}")

# Preprocessor Defines
target_compile_definitions(${TARGET_NAME} PRIVATE 
     $<$<CONFIG:debug>:DEBUG=1>
     $<$<CONFIG:release>:RELEASE=1>
     $<$<CONFIG:relwithdebinfo>:RELDEB=1>
     $<$<CONFIG:minsizerel>:MINREL=1>
     FLUGEL_BUILD_DLL=1)

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# glew
message(CHECK_START "Finding glew...")
find_package(glew CONFIG REQUIRED)
set(GLEW_LIBRARY GLEW::GLEW)
message(CHECK_PASS "glew included!")

# glad
message(CHECK_START "Finding glad...")
find_package(glad CONFIG REQUIRED)
set(GLAD_LIBRARY glad::glad)
message(CHECK_PASS "glad included!")

# glfw3
message(CHECK_START "Finding glfw3...")
find_package(glfw3 CONFIG REQUIRED)
set(GLFW_LIBRARY glfw)
message(CHECK_PASS "glfw3 included!")

# glm
message(CHECK_START "Finding glm...")
find_package(glm CONFIG REQUIRED)
set(GLM_LIBRARY glm::glm)
message(CHECK_PASS "glm included!")

# fmt
message(CHECK_START "Finding fmt...")
find_package(fmt CONFIG REQUIRED)
set(FMT_LIBRARY fmt::fmt-header-only)
message(CHECK_PASS "fmt included!")

# spdlog
message(CHECK_START "Finding spdlog...")
find_package(spdlog CONFIG REQUIRED)
set(SPDLOG_LIBRARY spdlog::spdlog_header_only) #spdlog::spdlog OR spdlog::spdlog_header_only
message(CHECK_PASS "spdlog included!")

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Define the include DIRs
include_directories("${SRC_DIR}" "${INCL_DIR}")

# Define the link libraries
link_directories(${LIB_DIR})

# Export the library's public header path to dependent targets
set(PUBLIC_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(${TARGET_NAME}
     INTERFACE
          "${PUBLIC_HEADER_FILES}"
)

# Precompiled Headers
target_precompile_headers(${TARGET_NAME}
     PUBLIC
          "${SRC_DIR}/flugel_pch.hpp"
)

# Put all libraries into a variable & link the libraries
set(LIBS 
     ${GLEW_LIBRARY}
     ${GLAD_LIBRARY}
     ${GLFW_LIBRARY}
     ${GLM_LIBRARY}
     ${FMT_LIBRARY}
     ${SPDLOG_LIBRARY})
target_link_libraries(${TARGET_NAME} ${LIBS})