# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.21)
project(sandbox VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME "SANDBOX")
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

# set(SOURCE_FILES
# ${SRC_DIR}/alpha.cpp
# )

# set(HEADER_FILES

# )

# ===================================================
# CONFIGURE ASSESTS HELPER FILE
# ===================================================
configure_file(src/helpers/RootDir.hpp.in src/helpers/RootDir.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/src)

# ===================================================
# ADD EXECUTABLE TARGET
# ===================================================
add_executable(${TARGET_NAME} 
  ${HEADER_FILES} 
  ${SOURCE_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES
  VERSION "${PROJECT_VERSION}"
  RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}")
message(DEBUG "App bin Dir: ${BIN_DIR}")

# Preprocessor Defines
target_compile_definitions(${TARGET_NAME} PRIVATE
  $<$<CONFIG:debug>:DEBUG=1 FLUGEL_ENABLE_ASSERTS=1>
  $<$<CONFIG:release>:RELEASE=1>
  $<$<CONFIG:relwithdebinfo>:RELDEB=1 FLUGEL_ENABLE_ASSERTS=1>
  $<$<CONFIG:minsizerel>:MINREL=1>)

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Define the include DIRs
#set(LIB_INCL ${flugel_engine_INCLUDE_DIRS})
target_include_directories(${TARGET_NAME}
  PRIVATE
    "${SRC_DIR}" "${INCL_DIR}"
)

# Define the link libraries
link_directories("${LIB_DIR}")

# Put all libraries into a variable & link the libraries with the executable
message(CHECK_START "Linking against Flugel Engine...")
set(LIBS "libflugel")
target_link_libraries(${TARGET_NAME} ${LIBS})
message(CHECK_PASS "linked!")
