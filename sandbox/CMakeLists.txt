# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.16)
project(sandbox VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME "SANDBOX")
message(STATUS "Configuring: ${PROJECT_NAME}")

# ===================================================
# COLLECT FILES
# ===================================================

set(SOURCE_FILES
  src/sandbox.cpp
)

# ===================================================
# ADD EXECUTABLE TARGET
# ===================================================
add_executable(${TARGET_NAME}
  ${SOURCE_FILES}
)

set_target_properties(${TARGET_NAME}
  PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}"
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
)

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Define the include DIRs
target_include_directories(${TARGET_NAME}
  PRIVATE
    "src" "include"
)

# Define the link libraries
target_link_directories(${TARGET_NAME}
  PRIVATE
    "lib"
)

# Put all libraries into a variable & link the libraries with the executable
message(CHECK_START "Linking against Flugel Engine...")
set(LIBS "flugel")
target_link_libraries(${TARGET_NAME}
  PRIVATE
    ${LIBS}
)
message(CHECK_PASS "linked!")

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
